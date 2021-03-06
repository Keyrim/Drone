﻿namespace Acc_Atenuation
{
    partial class Form1
    {
        /// <summary>
        /// Variable nécessaire au concepteur.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Nettoyage des ressources utilisées.
        /// </summary>
        /// <param name="disposing">true si les ressources managées doivent être supprimées ; sinon, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Code généré par le Concepteur Windows Form

        /// <summary>
        /// Méthode requise pour la prise en charge du concepteur - ne modifiez pas
        /// le contenu de cette méthode avec l'éditeur de code.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Form1));
            this.label_short_cut_list = new System.Windows.Forms.Label();
            this.label_conexion_state = new System.Windows.Forms.Label();
            this.serialPort_Arduino = new System.IO.Ports.SerialPort(this.components);
            this.label_global_power = new System.Windows.Forms.Label();
            this.numericUpDown_global_value = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_angle = new System.Windows.Forms.NumericUpDown();
            this.label_angle = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.label_loop_timer = new System.Windows.Forms.Label();
            this.numericUpDown_loop_timer = new System.Windows.Forms.NumericUpDown();
            this.pictureBox_angle = new System.Windows.Forms.PictureBox();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.button_conexion = new System.Windows.Forms.Button();
            this.button_motor_run = new System.Windows.Forms.Button();
            this.button_loop_timer = new System.Windows.Forms.Button();
            this.button_angle = new System.Windows.Forms.Button();
            this.button_complementary_filter = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_global_value)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_angle)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_loop_timer)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_angle)).BeginInit();
            this.SuspendLayout();
            // 
            // label_short_cut_list
            // 
            this.label_short_cut_list.AutoSize = true;
            this.label_short_cut_list.Location = new System.Drawing.Point(12, 73);
            this.label_short_cut_list.Name = "label_short_cut_list";
            this.label_short_cut_list.Size = new System.Drawing.Size(243, 117);
            this.label_short_cut_list.TabIndex = 0;
            this.label_short_cut_list.Text = resources.GetString("label_short_cut_list.Text");
            // 
            // label_conexion_state
            // 
            this.label_conexion_state.AutoSize = true;
            this.label_conexion_state.BackColor = System.Drawing.Color.GreenYellow;
            this.label_conexion_state.Location = new System.Drawing.Point(12, 32);
            this.label_conexion_state.Name = "label_conexion_state";
            this.label_conexion_state.Size = new System.Drawing.Size(118, 13);
            this.label_conexion_state.TabIndex = 1;
            this.label_conexion_state.Text = "Arduino Conexion State";
            // 
            // serialPort_Arduino
            // 
            this.serialPort_Arduino.PortName = "COM8";
            this.serialPort_Arduino.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.SerialPort_Arduino_DataReceived);
            // 
            // label_global_power
            // 
            this.label_global_power.AutoSize = true;
            this.label_global_power.Location = new System.Drawing.Point(278, 32);
            this.label_global_power.Name = "label_global_power";
            this.label_global_power.Size = new System.Drawing.Size(98, 13);
            this.label_global_power.TabIndex = 2;
            this.label_global_power.Text = "Global motor power";
            // 
            // numericUpDown_global_value
            // 
            this.numericUpDown_global_value.Location = new System.Drawing.Point(281, 48);
            this.numericUpDown_global_value.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numericUpDown_global_value.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown_global_value.Name = "numericUpDown_global_value";
            this.numericUpDown_global_value.Size = new System.Drawing.Size(95, 20);
            this.numericUpDown_global_value.TabIndex = 3;
            this.numericUpDown_global_value.Value = new decimal(new int[] {
            1100,
            0,
            0,
            0});
            this.numericUpDown_global_value.ValueChanged += new System.EventHandler(this.NumericUpDown_global_value_ValueChanged);
            // 
            // numericUpDown_angle
            // 
            this.numericUpDown_angle.DecimalPlaces = 3;
            this.numericUpDown_angle.Increment = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numericUpDown_angle.Location = new System.Drawing.Point(436, 48);
            this.numericUpDown_angle.Maximum = new decimal(new int[] {
            180,
            0,
            0,
            0});
            this.numericUpDown_angle.Name = "numericUpDown_angle";
            this.numericUpDown_angle.Size = new System.Drawing.Size(79, 20);
            this.numericUpDown_angle.TabIndex = 4;
            // 
            // label_angle
            // 
            this.label_angle.AutoSize = true;
            this.label_angle.Location = new System.Drawing.Point(433, 32);
            this.label_angle.Name = "label_angle";
            this.label_angle.Size = new System.Drawing.Size(82, 13);
            this.label_angle.TabIndex = 5;
            this.label_angle.Text = "Angle From Acc";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(0, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(35, 13);
            this.label1.TabIndex = 6;
            this.label1.Text = "label1";
            // 
            // label_loop_timer
            // 
            this.label_loop_timer.AutoSize = true;
            this.label_loop_timer.Location = new System.Drawing.Point(433, 82);
            this.label_loop_timer.Name = "label_loop_timer";
            this.label_loop_timer.Size = new System.Drawing.Size(63, 13);
            this.label_loop_timer.TabIndex = 7;
            this.label_loop_timer.Text = "Loop Timer ";
            // 
            // numericUpDown_loop_timer
            // 
            this.numericUpDown_loop_timer.Increment = new decimal(new int[] {
            0,
            0,
            0,
            0});
            this.numericUpDown_loop_timer.Location = new System.Drawing.Point(436, 98);
            this.numericUpDown_loop_timer.Maximum = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numericUpDown_loop_timer.Name = "numericUpDown_loop_timer";
            this.numericUpDown_loop_timer.Size = new System.Drawing.Size(67, 20);
            this.numericUpDown_loop_timer.TabIndex = 8;
            this.numericUpDown_loop_timer.ValueChanged += new System.EventHandler(this.NumericUpDown_loop_timer_ValueChanged);
            // 
            // pictureBox_angle
            // 
            this.pictureBox_angle.Location = new System.Drawing.Point(48, 235);
            this.pictureBox_angle.Name = "pictureBox_angle";
            this.pictureBox_angle.Size = new System.Drawing.Size(700, 180);
            this.pictureBox_angle.TabIndex = 9;
            this.pictureBox_angle.TabStop = false;
            this.pictureBox_angle.Paint += new System.Windows.Forms.PaintEventHandler(this.PictureBox_angle_Paint);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 20;
            this.timer1.Tick += new System.EventHandler(this.Timer1_Tick);
            // 
            // button_conexion
            // 
            this.button_conexion.Location = new System.Drawing.Point(637, 32);
            this.button_conexion.Name = "button_conexion";
            this.button_conexion.Size = new System.Drawing.Size(75, 23);
            this.button_conexion.TabIndex = 10;
            this.button_conexion.Text = "Conexion";
            this.button_conexion.UseVisualStyleBackColor = true;
            this.button_conexion.Click += new System.EventHandler(this.Button_conexion_Click);
            // 
            // button_motor_run
            // 
            this.button_motor_run.Location = new System.Drawing.Point(637, 62);
            this.button_motor_run.Name = "button_motor_run";
            this.button_motor_run.Size = new System.Drawing.Size(75, 23);
            this.button_motor_run.TabIndex = 11;
            this.button_motor_run.Text = "Run motors";
            this.button_motor_run.UseVisualStyleBackColor = true;
            this.button_motor_run.Click += new System.EventHandler(this.Button_motor_run_Click);
            // 
            // button_loop_timer
            // 
            this.button_loop_timer.Location = new System.Drawing.Point(637, 92);
            this.button_loop_timer.Name = "button_loop_timer";
            this.button_loop_timer.Size = new System.Drawing.Size(75, 23);
            this.button_loop_timer.TabIndex = 12;
            this.button_loop_timer.Text = "Loop timer";
            this.button_loop_timer.UseVisualStyleBackColor = true;
            this.button_loop_timer.Click += new System.EventHandler(this.Button_loop_timer_Click);
            // 
            // button_angle
            // 
            this.button_angle.Location = new System.Drawing.Point(637, 122);
            this.button_angle.Name = "button_angle";
            this.button_angle.Size = new System.Drawing.Size(75, 23);
            this.button_angle.TabIndex = 13;
            this.button_angle.Text = "Angle";
            this.button_angle.UseVisualStyleBackColor = true;
            this.button_angle.Click += new System.EventHandler(this.Button_angle_Click);
            // 
            // button_complementary_filter
            // 
            this.button_complementary_filter.Location = new System.Drawing.Point(637, 151);
            this.button_complementary_filter.Name = "button_complementary_filter";
            this.button_complementary_filter.Size = new System.Drawing.Size(128, 23);
            this.button_complementary_filter.TabIndex = 14;
            this.button_complementary_filter.Text = "Complementary filter";
            this.button_complementary_filter.UseVisualStyleBackColor = true;
            this.button_complementary_filter.Click += new System.EventHandler(this.Button_complementary_filter_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.button_complementary_filter);
            this.Controls.Add(this.button_angle);
            this.Controls.Add(this.button_loop_timer);
            this.Controls.Add(this.button_motor_run);
            this.Controls.Add(this.button_conexion);
            this.Controls.Add(this.pictureBox_angle);
            this.Controls.Add(this.numericUpDown_loop_timer);
            this.Controls.Add(this.label_loop_timer);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.label_angle);
            this.Controls.Add(this.numericUpDown_angle);
            this.Controls.Add(this.numericUpDown_global_value);
            this.Controls.Add(this.label_global_power);
            this.Controls.Add(this.label_conexion_state);
            this.Controls.Add(this.label_short_cut_list);
            this.Name = "Form1";
            this.Text = "Form1";
            this.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.Form1_KeyPress);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_global_value)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_angle)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_loop_timer)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox_angle)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Label label_short_cut_list;
        private System.Windows.Forms.Label label_conexion_state;
        private System.IO.Ports.SerialPort serialPort_Arduino;
        private System.Windows.Forms.Label label_global_power;
        private System.Windows.Forms.NumericUpDown numericUpDown_global_value;
        private System.Windows.Forms.NumericUpDown numericUpDown_angle;
        private System.Windows.Forms.Label label_angle;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label_loop_timer;
        private System.Windows.Forms.NumericUpDown numericUpDown_loop_timer;
        private System.Windows.Forms.PictureBox pictureBox_angle;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.Button button_conexion;
        private System.Windows.Forms.Button button_motor_run;
        private System.Windows.Forms.Button button_loop_timer;
        private System.Windows.Forms.Button button_angle;
        private System.Windows.Forms.Button button_complementary_filter;
    }
}

