using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace _1__DOF_Stabilisation_Remote
{
    class Axe_animation
    {
        public double angle = 0;
        public PictureBox pictureBox = new PictureBox();
        public Pen pen = new Pen(Brushes.Black);


        public Axe_animation(int width, int height)
        {
            pen.Width = 10;
            pictureBox.Width = width;
            pictureBox.Height = height;
            pictureBox.BorderStyle = BorderStyle.FixedSingle;
            pictureBox.Visible = true;
            pictureBox.Paint += picture_box_paint;
            pictureBox.BackColor = Color.AliceBlue;
        }

        public void set_window(int left_side, int top)
        {
            
            pictureBox.Location = new Point(left_side, top);
        }

        private void picture_box_paint(object sender, PaintEventArgs e)
        {
            e.Graphics.DrawLine(pen, (float)Math.Cos(angle/180*Math.PI)*100+ pictureBox.Width / 2,
                -(float)Math.Sin(angle / 180 * Math.PI) * 100 + pictureBox.Height / 2 , 
                pictureBox.Width / 2, pictureBox.Height / 2);          
        }


        


    }
}
