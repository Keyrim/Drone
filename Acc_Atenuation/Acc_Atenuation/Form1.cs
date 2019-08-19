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
        Queue<int> points = new Queue<int>();
        const int queue_shape = 140;
        decimal space;
        Pen pen = new Pen(Color.Black);


        public Form1()
        {
            InitializeComponent();
            this.KeyPreview = true;
            space = (decimal)pictureBox_angle.Width / (decimal)queue_shape;
            pen.Width = 3;
        }

        private void SerialPort_Arduino_DataReceived(object sender, System.IO.Ports.SerialDataReceivedEventArgs e)
        {
            while(serialPort_Arduino.BytesToRead>0)
            {
                int number = Convert.ToInt32(serialPort_Arduino.ReadLine());
                int id = number & 15;
                number -= id;
                number = number >> 4;

                if (id == 0)
                {
                    numericUpDown_angle.Invoke((MethodInvoker)delegate { numericUpDown_angle.Value = (decimal)number / (decimal)1000; });
                    add_angle_to_draw(number / 1000);
                    
                }
                else if (id == 1) numericUpDown_loop_timer.Invoke((MethodInvoker)delegate { numericUpDown_loop_timer.Value = (decimal)number; });



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

        private void add_angle_to_draw(int angle_to_add)
        {
            if (points.Count() >= queue_shape)
            {
                points.Dequeue();
                points.Enqueue(angle_to_add);
            }
            else points.Enqueue(angle_to_add);
        }

        private void Form1_KeyPress(object sender, KeyPressEventArgs e)
        {
            string chr = e.KeyChar.ToString();
            if (chr == "O")open_arduino();           
            if (chr == "S") if (serialPort_Arduino.IsOpen) serialPort_Arduino.Close();
            if (chr == "G") write_arduino(1, (int)numericUpDown_global_value.Value);
            if (chr == "M") write_arduino(0, 1);
            if (chr == "F") write_arduino(0, 3);
            if (chr == "A") write_arduino(0, 0);
            if (chr == "L") write_arduino(0, 2);
            if (chr == " ") write_arduino(1, 1000);
        }

        private void PictureBox_angle_Paint(object sender, PaintEventArgs e)
        {
            if(points.Count() > 1)
                for (int i = 1; i < points.Count()-1; i++)            
                    e.Graphics.DrawLine(pen, (int)(i*space-space), points.ToArray()[i-1], (int)(i*space), points.ToArray()[i]);
            
        }

        private void Timer1_Tick(object sender, EventArgs e)
        {
            pictureBox_angle.Invalidate();
        }

        //Buttons that change boolen value as the keyboard control 
        private void Button_conexion_Click(object sender, EventArgs e)
        {
            open_arduino();
        }
        private void Button_motor_run_Click(object sender, EventArgs e)
        {
            write_arduino(1, (int)numericUpDown_global_value.Value);
        }
        private void Button_loop_timer_Click(object sender, EventArgs e)
        {
            write_arduino(0, 2);
        }
        private void Button_angle_Click(object sender, EventArgs e)
        {
            write_arduino(0, 0);
        }
        private void Button_complementary_filter_Click(object sender, EventArgs e)
        {
            write_arduino(0, 4);
        }
    }
}
