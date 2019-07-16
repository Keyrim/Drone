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
        Pen dark_blue_pen = new Pen(Brushes.DarkBlue);

        
        public Form1()
        {
            InitializeComponent();
            dark_blue_pen.Width = 8.0F;
            dark_blue_pen.LineJoin = System.Drawing.Drawing2D.LineJoin.Bevel;
            
        }

        private void PictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawLine(dark_blue_pen, 0, 0, 500, 500);
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            pictureBox1.Invalidate();
        }
    }
}
