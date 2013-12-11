namespace KorRail_Bid_4_HM
{
    partial class MainFrame
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.StartButton = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.IDTextBox = new System.Windows.Forms.TextBox();
            this.PWTextBox = new System.Windows.Forms.TextBox();
            this.label2 = new System.Windows.Forms.Label();
            this.dateTimePicker1 = new System.Windows.Forms.DateTimePicker();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this.SeatCombo = new System.Windows.Forms.ComboBox();
            this.PersonCombo = new System.Windows.Forms.ComboBox();
            this.Browser = new System.Windows.Forms.WebBrowser();
            this.label3 = new System.Windows.Forms.Label();
            this.JobLogLabel = new System.Windows.Forms.Label();
            this.TimeLabel = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.Timer1 = new System.Windows.Forms.Timer(this.components);
            this.UpDownCombo = new System.Windows.Forms.ComboBox();
            this.SuspendLayout();
            // 
            // StartButton
            // 
            this.StartButton.Location = new System.Drawing.Point(14, 102);
            this.StartButton.Name = "StartButton";
            this.StartButton.Size = new System.Drawing.Size(142, 23);
            this.StartButton.TabIndex = 0;
            this.StartButton.Text = "Start";
            this.StartButton.UseVisualStyleBackColor = true;
            this.StartButton.Click += new System.EventHandler(this.StartButton_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(12, 53);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 12);
            this.label1.TabIndex = 1;
            this.label1.Text = "ID : ";
            // 
            // IDTextBox
            // 
            this.IDTextBox.Location = new System.Drawing.Point(56, 48);
            this.IDTextBox.Name = "IDTextBox";
            this.IDTextBox.Size = new System.Drawing.Size(100, 21);
            this.IDTextBox.TabIndex = 2;
            this.IDTextBox.Text = "1240521669";
            // 
            // PWTextBox
            // 
            this.PWTextBox.Location = new System.Drawing.Point(56, 75);
            this.PWTextBox.Name = "PWTextBox";
            this.PWTextBox.PasswordChar = '*';
            this.PWTextBox.Size = new System.Drawing.Size(100, 21);
            this.PWTextBox.TabIndex = 4;
            this.PWTextBox.Text = "3544";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 80);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(31, 12);
            this.label2.TabIndex = 3;
            this.label2.Text = "PW :";
            // 
            // dateTimePicker1
            // 
            this.dateTimePicker1.CustomFormat = "";
            this.dateTimePicker1.Font = new System.Drawing.Font("Verdana", 9F);
            this.dateTimePicker1.Format = System.Windows.Forms.DateTimePickerFormat.Short;
            this.dateTimePicker1.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.dateTimePicker1.Location = new System.Drawing.Point(12, 149);
            this.dateTimePicker1.Name = "dateTimePicker1";
            this.dateTimePicker1.Size = new System.Drawing.Size(142, 22);
            this.dateTimePicker1.TabIndex = 7;
            this.dateTimePicker1.Value = new System.DateTime(2013, 5, 22, 0, 0, 0, 0);
            // 
            // listBox1
            // 
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 12;
            this.listBox1.Items.AddRange(new object[] {
            "옵션따위는 적용 안되니 ",
            "고쳐야 소용 없음"});
            this.listBox1.Location = new System.Drawing.Point(14, 285);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(142, 472);
            this.listBox1.TabIndex = 8;
            // 
            // SeatCombo
            // 
            this.SeatCombo.FormattingEnabled = true;
            this.SeatCombo.Items.AddRange(new object[] {
            "역방향석"});
            this.SeatCombo.Location = new System.Drawing.Point(12, 226);
            this.SeatCombo.Name = "SeatCombo";
            this.SeatCombo.Size = new System.Drawing.Size(142, 20);
            this.SeatCombo.TabIndex = 16;
            this.SeatCombo.Text = "역방향석";
            // 
            // PersonCombo
            // 
            this.PersonCombo.FormattingEnabled = true;
            this.PersonCombo.Items.AddRange(new object[] {
            "1명"});
            this.PersonCombo.Location = new System.Drawing.Point(12, 200);
            this.PersonCombo.Name = "PersonCombo";
            this.PersonCombo.Size = new System.Drawing.Size(142, 20);
            this.PersonCombo.TabIndex = 17;
            this.PersonCombo.Text = "1명";
            // 
            // Browser
            // 
            this.Browser.Location = new System.Drawing.Point(162, 8);
            this.Browser.MinimumSize = new System.Drawing.Size(20, 20);
            this.Browser.Name = "Browser";
            this.Browser.Size = new System.Drawing.Size(1110, 749);
            this.Browser.TabIndex = 19;
            this.Browser.Url = new System.Uri("", System.UriKind.Relative);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(12, 9);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(79, 12);
            this.label3.TabIndex = 20;
            this.label3.Text = "Current Time";
            // 
            // JobLogLabel
            // 
            this.JobLogLabel.AutoSize = true;
            this.JobLogLabel.Location = new System.Drawing.Point(10, 270);
            this.JobLogLabel.Name = "JobLogLabel";
            this.JobLogLabel.Size = new System.Drawing.Size(46, 12);
            this.JobLogLabel.TabIndex = 21;
            this.JobLogLabel.Text = "JobLog";
            // 
            // TimeLabel
            // 
            this.TimeLabel.AutoSize = true;
            this.TimeLabel.Location = new System.Drawing.Point(43, 28);
            this.TimeLabel.Name = "TimeLabel";
            this.TimeLabel.Size = new System.Drawing.Size(56, 12);
            this.TimeLabel.TabIndex = 22;
            this.TimeLabel.Text = "AM 12:00";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(12, 134);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(83, 12);
            this.label4.TabIndex = 23;
            this.label4.Text = "Wanted Date :";
            // 
            // Timer1
            // 
            this.Timer1.Interval = 1000;
            this.Timer1.Tick += new System.EventHandler(this.Timer1_Tick);
            // 
            // UpDownCombo
            // 
            this.UpDownCombo.FormattingEnabled = true;
            this.UpDownCombo.Items.AddRange(new object[] {
            "광명 -> 김천구미",
            "김천구미 - > 수원"});
            this.UpDownCombo.Location = new System.Drawing.Point(12, 177);
            this.UpDownCombo.Name = "UpDownCombo";
            this.UpDownCombo.Size = new System.Drawing.Size(142, 20);
            this.UpDownCombo.TabIndex = 24;
            this.UpDownCombo.Text = "광명 -> 김천구미";
            // 
            // MainFrame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(7F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1272, 769);
            this.Controls.Add(this.UpDownCombo);
            this.Controls.Add(this.label4);
            this.Controls.Add(this.TimeLabel);
            this.Controls.Add(this.JobLogLabel);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.Browser);
            this.Controls.Add(this.PersonCombo);
            this.Controls.Add(this.SeatCombo);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.dateTimePicker1);
            this.Controls.Add(this.PWTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.IDTextBox);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.StartButton);
            this.Name = "MainFrame";
            this.Text = "실패는 언제든 가능한 것이니 좌절금지";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button StartButton;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.TextBox IDTextBox;
        private System.Windows.Forms.TextBox PWTextBox;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.DateTimePicker dateTimePicker1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.ComboBox SeatCombo;
        private System.Windows.Forms.ComboBox PersonCombo;
        private System.Windows.Forms.WebBrowser Browser;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label JobLogLabel;
        private System.Windows.Forms.Label TimeLabel;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Timer Timer1;
        private System.Windows.Forms.ComboBox UpDownCombo;
    }
}

