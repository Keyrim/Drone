using System;
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
        Axe_animation axe = new Axe_animation(300, 200);
        

        
        public Form1()
        {
            InitializeComponent();
            axe.set_window(this.Width/2 -150, this.Height/2-100);
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
                try
                {
                    axe.angle = -1 * Convert.ToInt32(message, new CultureInfo("en-US"));
                }
                catch { }
                axe.pictureBox.Invalidate();
                
                textBox_informations.Invoke((MethodInvoker)delegate
                {
                    textBox_conexion_state.Text = axe.angle.ToString();
                    
                });

            }
            

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            if (arduino.IsOpen) arduino.Close();
        }
    }
}
