namespace _1__DOF_Stabilisation_Remote
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
            this.arduino = new System.IO.Ports.SerialPort(this.components);
            this.numericUpDown_arduino_port = new System.Windows.Forms.NumericUpDown();
            this.textBox_port_com = new System.Windows.Forms.TextBox();
            this.button_conexion = new System.Windows.Forms.Button();
            this.textBox_conexion_state = new System.Windows.Forms.TextBox();
            this.textBox_informations = new System.Windows.Forms.TextBox();
            this.numericUpDown_p = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_d = new System.Windows.Forms.NumericUpDown();
            this.numericUpDown_i = new System.Windows.Forms.NumericUpDown();
            this.label_pid_settings = new System.Windows.Forms.Label();
            this.button_on = new System.Windows.Forms.Button();
            this.button_off = new System.Windows.Forms.Button();
            this.label_global_powe_setting = new System.Windows.Forms.Label();
            this.numericUpDown_global_power = new System.Windows.Forms.NumericUpDown();
            this.button_send_pid = new System.Windows.Forms.Button();
            this.timer_frequence = new System.Windows.Forms.Timer(this.components);
            this.label_consigne = new System.Windows.Forms.Label();
            this.numericUpDown_consigne = new System.Windows.Forms.NumericUpDown();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_arduino_port)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_p)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_d)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_i)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_global_power)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_consigne)).BeginInit();
            this.SuspendLayout();
            // 
            // arduino
            // 
            this.arduino.BaudRate = 115200;
            this.arduino.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.Arduino_DataReceived);
            // 
            // numericUpDown_arduino_port
            // 
            this.numericUpDown_arduino_port.Location = new System.Drawing.Point(160, 29);
            this.numericUpDown_arduino_port.Maximum = new decimal(new int[] {
            15,
            0,
            0,
            0});
            this.numericUpDown_arduino_port.Name = "numericUpDown_arduino_port";
            this.numericUpDown_arduino_port.Size = new System.Drawing.Size(38, 20);
            this.numericUpDown_arduino_port.TabIndex = 2;
            this.numericUpDown_arduino_port.Value = new decimal(new int[] {
            6,
            0,
            0,
            0});
            // 
            // textBox_port_com
            // 
            this.textBox_port_com.Location = new System.Drawing.Point(93, 28);
            this.textBox_port_com.Name = "textBox_port_com";
            this.textBox_port_com.Size = new System.Drawing.Size(61, 20);
            this.textBox_port_com.TabIndex = 3;
            this.textBox_port_com.Text = "Port COM :";
            // 
            // button_conexion
            // 
            this.button_conexion.Location = new System.Drawing.Point(12, 25);
            this.button_conexion.Name = "button_conexion";
            this.button_conexion.Size = new System.Drawing.Size(75, 23);
            this.button_conexion.TabIndex = 4;
            this.button_conexion.Text = "Conexion Arduino";
            this.button_conexion.UseVisualStyleBackColor = true;
            this.button_conexion.Click += new System.EventHandler(this.Button_conexion_Click);
            // 
            // textBox_conexion_state
            // 
            this.textBox_conexion_state.Location = new System.Drawing.Point(12, 54);
            this.textBox_conexion_state.Name = "textBox_conexion_state";
            this.textBox_conexion_state.Size = new System.Drawing.Size(186, 20);
            this.textBox_conexion_state.TabIndex = 5;
            this.textBox_conexion_state.Text = "Conexion State : Not Conected";
            // 
            // textBox_informations
            // 
            this.textBox_informations.Location = new System.Drawing.Point(12, 80);
            this.textBox_informations.Multiline = true;
            this.textBox_informations.Name = "textBox_informations";
            this.textBox_informations.Size = new System.Drawing.Size(186, 45);
            this.textBox_informations.TabIndex = 6;
            // 
            // numericUpDown_p
            // 
            this.numericUpDown_p.DecimalPlaces = 3;
            this.numericUpDown_p.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDown_p.Location = new System.Drawing.Point(592, 45);
            this.numericUpDown_p.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown_p.Name = "numericUpDown_p";
            this.numericUpDown_p.Size = new System.Drawing.Size(58, 20);
            this.numericUpDown_p.TabIndex = 7;
            // 
            // numericUpDown_d
            // 
            this.numericUpDown_d.DecimalPlaces = 3;
            this.numericUpDown_d.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDown_d.Location = new System.Drawing.Point(720, 45);
            this.numericUpDown_d.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown_d.Name = "numericUpDown_d";
            this.numericUpDown_d.Size = new System.Drawing.Size(58, 20);
            this.numericUpDown_d.TabIndex = 8;
            // 
            // numericUpDown_i
            // 
            this.numericUpDown_i.DecimalPlaces = 3;
            this.numericUpDown_i.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numericUpDown_i.Location = new System.Drawing.Point(656, 45);
            this.numericUpDown_i.Maximum = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown_i.Name = "numericUpDown_i";
            this.numericUpDown_i.Size = new System.Drawing.Size(58, 20);
            this.numericUpDown_i.TabIndex = 9;
            // 
            // label_pid_settings
            // 
            this.label_pid_settings.AutoSize = true;
            this.label_pid_settings.Location = new System.Drawing.Point(589, 25);
            this.label_pid_settings.Name = "label_pid_settings";
            this.label_pid_settings.Size = new System.Drawing.Size(70, 13);
            this.label_pid_settings.TabIndex = 10;
            this.label_pid_settings.Text = "PID settings :";
            // 
            // button_on
            // 
            this.button_on.Location = new System.Drawing.Point(217, 29);
            this.button_on.Name = "button_on";
            this.button_on.Size = new System.Drawing.Size(75, 23);
            this.button_on.TabIndex = 11;
            this.button_on.Text = "ON";
            this.button_on.UseVisualStyleBackColor = true;
            this.button_on.Click += new System.EventHandler(this.Button_on_Click);
            // 
            // button_off
            // 
            this.button_off.Location = new System.Drawing.Point(298, 29);
            this.button_off.Name = "button_off";
            this.button_off.Size = new System.Drawing.Size(75, 23);
            this.button_off.TabIndex = 12;
            this.button_off.Text = "OFF";
            this.button_off.UseVisualStyleBackColor = true;
            this.button_off.Click += new System.EventHandler(this.Button_off_Click);
            // 
            // label_global_powe_setting
            // 
            this.label_global_powe_setting.AutoSize = true;
            this.label_global_powe_setting.Location = new System.Drawing.Point(214, 61);
            this.label_global_powe_setting.Name = "label_global_powe_setting";
            this.label_global_powe_setting.Size = new System.Drawing.Size(106, 13);
            this.label_global_powe_setting.TabIndex = 13;
            this.label_global_powe_setting.Text = "Global Power Setting";
            // 
            // numericUpDown_global_power
            // 
            this.numericUpDown_global_power.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown_global_power.Location = new System.Drawing.Point(217, 80);
            this.numericUpDown_global_power.Maximum = new decimal(new int[] {
            2000,
            0,
            0,
            0});
            this.numericUpDown_global_power.Minimum = new decimal(new int[] {
            1000,
            0,
            0,
            0});
            this.numericUpDown_global_power.Name = "numericUpDown_global_power";
            this.numericUpDown_global_power.Size = new System.Drawing.Size(103, 20);
            this.numericUpDown_global_power.TabIndex = 14;
            this.numericUpDown_global_power.Value = new decimal(new int[] {
            1100,
            0,
            0,
            0});
            // 
            // button_send_pid
            // 
            this.button_send_pid.Location = new System.Drawing.Point(592, 80);
            this.button_send_pid.Name = "button_send_pid";
            this.button_send_pid.Size = new System.Drawing.Size(186, 23);
            this.button_send_pid.TabIndex = 15;
            this.button_send_pid.Text = "Send PID settings to the Arduino";
            this.button_send_pid.UseVisualStyleBackColor = true;
            this.button_send_pid.Click += new System.EventHandler(this.Button_send_pid_Click);
            // 
            // timer_frequence
            // 
            this.timer_frequence.Enabled = true;
            this.timer_frequence.Interval = 16;
            this.timer_frequence.Tick += new System.EventHandler(this.Timer_frequence_Tick);
            // 
            // label_consigne
            // 
            this.label_consigne.AutoSize = true;
            this.label_consigne.Location = new System.Drawing.Point(394, 34);
            this.label_consigne.Name = "label_consigne";
            this.label_consigne.Size = new System.Drawing.Size(51, 13);
            this.label_consigne.TabIndex = 16;
            this.label_consigne.Text = "Consigne";
            // 
            // numericUpDown_consigne
            // 
            this.numericUpDown_consigne.Increment = new decimal(new int[] {
            10,
            0,
            0,
            0});
            this.numericUpDown_consigne.Location = new System.Drawing.Point(397, 61);
            this.numericUpDown_consigne.Maximum = new decimal(new int[] {
            160,
            0,
            0,
            0});
            this.numericUpDown_consigne.Minimum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numericUpDown_consigne.Name = "numericUpDown_consigne";
            this.numericUpDown_consigne.Size = new System.Drawing.Size(120, 20);
            this.numericUpDown_consigne.TabIndex = 17;
            this.numericUpDown_consigne.Value = new decimal(new int[] {
            90,
            0,
            0,
            0});
            this.numericUpDown_consigne.ValueChanged += new System.EventHandler(this.NumericUpDown_consigne_ValueChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.numericUpDown_consigne);
            this.Controls.Add(this.label_consigne);
            this.Controls.Add(this.button_send_pid);
            this.Controls.Add(this.numericUpDown_global_power);
            this.Controls.Add(this.label_global_powe_setting);
            this.Controls.Add(this.button_off);
            this.Controls.Add(this.button_on);
            this.Controls.Add(this.label_pid_settings);
            this.Controls.Add(this.numericUpDown_i);
            this.Controls.Add(this.numericUpDown_d);
            this.Controls.Add(this.numericUpDown_p);
            this.Controls.Add(this.textBox_informations);
            this.Controls.Add(this.textBox_conexion_state);
            this.Controls.Add(this.button_conexion);
            this.Controls.Add(this.textBox_port_com);
            this.Controls.Add(this.numericUpDown_arduino_port);
            this.Name = "Form1";
            this.Text = "Form1";
            this.FormClosed += new System.Windows.Forms.FormClosedEventHandler(this.Form1_FormClosed);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_arduino_port)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_p)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_d)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_i)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_global_power)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_consigne)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.IO.Ports.SerialPort arduino;
        private System.Windows.Forms.NumericUpDown numericUpDown_arduino_port;
        private System.Windows.Forms.TextBox textBox_port_com;
        private System.Windows.Forms.Button button_conexion;
        private System.Windows.Forms.TextBox textBox_conexion_state;
        private System.Windows.Forms.TextBox textBox_informations;
        private System.Windows.Forms.NumericUpDown numericUpDown_p;
        private System.Windows.Forms.NumericUpDown numericUpDown_d;
        private System.Windows.Forms.NumericUpDown numericUpDown_i;
        private System.Windows.Forms.Label label_pid_settings;
        private System.Windows.Forms.Button button_on;
        private System.Windows.Forms.Button button_off;
        private System.Windows.Forms.Label label_global_powe_setting;
        private System.Windows.Forms.NumericUpDown numericUpDown_global_power;
        private System.Windows.Forms.Button button_send_pid;
        private System.Windows.Forms.Timer timer_frequence;
        private System.Windows.Forms.Label label_consigne;
        private System.Windows.Forms.NumericUpDown numericUpDown_consigne;
    }
}

