using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Acc_Atenuation
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.KeyPreview = true;
        }

        private void SerialPort_Arduino_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            while(serialPort_Arduino.BytesToRead>0)
            {
                int number = Convert.ToInt32(serialPort_Arduino.ReadLine());
                int id = number & 15;
                number -= id;
                number = number >> 4;

                if (id == 0) numericUpDown_angle.Invoke((MethodInvoker)
                    delegate { numericUpDown_angle.Value = (decimal)number / (decimal)1000; });




            }


        }

        private void write_arduino(int index, int value)
        {
            value = value << 4;
            value += index;
                serialPort_Arduino.WriteLine(value.ToString());
        }

        private void NumericUpDown_global_value_ValueChanged(object sender, EventArgs e)
        {
            write_arduino(1, (int)numericUpDown_global_value.Value);
        }

        private void NumericUpDown_loop_timer_ValueChanged(object sender, EventArgs e)
        {
            write_arduino(0, 2);
        }
        private bool open_arduino()
        {
            try
            {
                serialPort_Arduino.Open();
                label_conexion_state.BackColor = Color.Green;
                return true;

            }
            catch
            {
                return false;
            }
        }

        

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            string chr = e.KeyChar.ToString();
            if (chr == "O")
            {
                open_arduino();
                label1.Text = "Open";
            }
            if (chr == "S") if (serialPort_Arduino.IsOpen) serialPort_Arduino.Close();
            if (chr == "G") write_arduino(1, (int)numericUpDown_global_value.Value);
            if (chr == "M") write_arduino(0, 1);
            if (chr == "F") write_arduino(0, 3);
            if (chr == "A") write_arduino(0, 0);
            if (chr == "L") write_arduino(0, 2);
        }


    }
}
