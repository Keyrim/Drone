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
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_arduino_port)).BeginInit();
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
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(784, 461);
            this.Controls.Add(this.textBox_informations);
            this.Controls.Add(this.textBox_conexion_state);
            this.Controls.Add(this.button_conexion);
            this.Controls.Add(this.textBox_port_com);
            this.Controls.Add(this.numericUpDown_arduino_port);
            this.Name = "Form1";
            this.Text = "Form1";
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown_arduino_port)).EndInit();
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
    }
}

