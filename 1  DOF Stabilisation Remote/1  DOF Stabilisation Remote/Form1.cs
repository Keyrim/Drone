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
        Axe_animation axe = new Axe_animation(500, 500);
        

        
        public Form1()
        {
            InitializeComponent();
            axe.set_window(this.Width/2 -250, this.Height/2-250);
            this.Controls.Add(axe.pictureBox);
            
            
        }


        private void Button1_Click(object sender, EventArgs e)
        {
            axe.pictureBox.Invalidate();
        }
    }
}
