﻿using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;  
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Globalization;

namespace _1__DOF_Stabilisation_Remote
{
    public partial class Form1 : Form
    {
        Axe_animation axe = new Axe_animation(400, 200);
        

        
        public Form1()
        {
            InitializeComponent();
            axe.set_window(this.Width/2 -200, this.Height/2-100);
            this.Controls.Add(axe.pictureBox);     
            
        }


        

        private void Button_conexion_Click(object sender, EventArgs e)
        {
            try
            {
                int port_number = (int)numericUpDown_arduino_port.Value;
                arduino.PortName = "COM" + port_number.ToString() ;
                arduino.Open();
                textBox_conexion_state.Invoke((MethodInvoker)delegate {
                    textBox_conexion_state.Text = "Conexion State = Conected"; });

            }
            catch
            {
                textBox_conexion_state.Invoke((MethodInvoker)delegate {
                    textBox_conexion_state.Text = "Conexion State = Not Conected"; });
            }
                
        }

        private void Arduino_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            while (arduino.BytesToRead > 0)
            {
                string message = arduino.ReadLine();
                int msg_number = Convert.ToInt32(message);
                int indice = msg_number & 15;
                msg_number = (msg_number - indice) >> 4;
                textBox_informations.Invoke((MethodInvoker)delegate
                {
                    textBox_informations.Text = indice.ToString() + "\t" +  msg_number.ToString();
                });
                //Index 0 is for the angle
                //      1 for the p corection
                //      3 for the I corection
                //      4 for the d corection
                if (indice == 0)        axe.angle = -msg_number;      
                else if (indice == 1)   axe.p_value = msg_number;
                else if (indice == 2) axe.p_value = -msg_number;
                else if (indice == 3) axe.i_value = msg_number;
                else if (indice == 4) axe.i_value = -msg_number;
                else if (indice == 5) axe.d_value = msg_number;
                else if (indice == 6) axe.d_value = -msg_number;
                



            }


        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (arduino.IsOpen) arduino.Close();
        }

        private void Button_on_Click(object sender, EventArgs e)
        {
            send_msg(1, (int)numericUpDown_global_power.Value);
        }

        private void send_msg(int indice, int value )
        {
            //0 is for a power off, value is 0 
            //1 is for a power on sending the global power setting as value
            //Values for pid setting are sent as integerso we multiply the value by 1000  before sending them
            //2 is for a p setting, the value sent is the p value times 1000
            //3 is for a i setting, the value sent is the i value times 1000
            //4 is for a d setting, the value sent is the d value times 1000
            //5 is to change the consigne value
            int valeur = value << 4;
            valeur += indice;

            arduino.WriteLine(valeur.ToString());
        }

        private void Button_off_Click(object sender, EventArgs e)
        {
            send_msg(0, 0);
        }

        private void Button_send_pid_Click(object sender, EventArgs e)
        {
            send_msg(2, (int)(numericUpDown_p.Value * 1000));
            send_msg(3, (int)(numericUpDown_i.Value * 1000));
            send_msg(4, (int)(numericUpDown_d.Value * 1000));


        }

        private void Timer_frequence_Tick(object sender, EventArgs e)
        {
            axe.pictureBox.Invalidate();
        }

        private void NumericUpDown_consigne_ValueChanged(object sender, EventArgs e)
        {
            send_msg(5, (int)numericUpDown_consigne.Value);
        }
    }
}
