using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

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
            string message = arduino.ReadLine();
            textBox_informations.Invoke((MethodInvoker)delegate { textBox_informations.Text = message; });

        }
    }
}
