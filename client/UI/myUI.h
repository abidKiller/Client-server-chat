#pragma once

namespace UI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for myUI
	/// </summary>
	public ref class myUI : public System::Windows::Forms::Form
	{
	public:
		myUI(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~myUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	protected:
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::PictureBox^  pictureBox3;
	private: System::Windows::Forms::TextBox^  userName;
	private: System::Windows::Forms::Button^  login;



	private: System::Windows::Forms::TextBox^  password;


	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel1;
	private: System::Windows::Forms::TableLayoutPanel^  tableLayoutPanel2;

	private: System::Windows::Forms::Button^  exit;
	private: System::Windows::Forms::Button^  regis;

	private: System::Windows::Forms::Button^  exiButton;


	private:
		int passpress = 0;

	public:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(myUI::typeid));
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox3 = (gcnew System::Windows::Forms::PictureBox());
			this->userName = (gcnew System::Windows::Forms::TextBox());
			this->login = (gcnew System::Windows::Forms::Button());
			this->password = (gcnew System::Windows::Forms::TextBox());
			this->tableLayoutPanel1 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->tableLayoutPanel2 = (gcnew System::Windows::Forms::TableLayoutPanel());
			this->exit = (gcnew System::Windows::Forms::Button());
			this->regis = (gcnew System::Windows::Forms::Button());
			this->exiButton = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->BeginInit();
			this->SuspendLayout();
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->Location = System::Drawing::Point(128, 58);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(93, 80);
			this->pictureBox1->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox1->TabIndex = 0;
			this->pictureBox1->TabStop = false;
			
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(47, 198);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(34, 29);
			this->pictureBox2->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox2->TabIndex = 1;
			this->pictureBox2->TabStop = false;
			this->pictureBox2->Click += gcnew System::EventHandler(this, &myUI::pictureBox2_Click);
			// 
			// pictureBox3
			// 
			this->pictureBox3->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"pictureBox3.Image")));
			this->pictureBox3->Location = System::Drawing::Point(47, 250);
			this->pictureBox3->Name = L"pictureBox3";
			this->pictureBox3->Size = System::Drawing::Size(34, 33);
			this->pictureBox3->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pictureBox3->TabIndex = 2;
			this->pictureBox3->TabStop = false;
			this->pictureBox3->Click += gcnew System::EventHandler(this, &myUI::pictureBox3_Click);
			// 
			// userName
			// 
			this->userName->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(49)));
			this->userName->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->userName->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->userName->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->userName->HideSelection = false;
			this->userName->Location = System::Drawing::Point(87, 207);
			this->userName->Multiline = true;
			this->userName->Name = L"userName";
			this->userName->Size = System::Drawing::Size(163, 21);
			this->userName->TabIndex = 3;
			this->userName->TabStop = false;
			this->userName->Text = L"Username";
			this->userName->TextChanged += gcnew System::EventHandler(this, &myUI::textBox1_TextChanged);
			// 
			// login
			// 
			this->login->BackColor = System::Drawing::SystemColors::MenuHighlight;
			this->login->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->login->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->login->ForeColor = System::Drawing::SystemColors::ControlText;
			this->login->Location = System::Drawing::Point(47, 352);
			this->login->Name = L"login";
			this->login->Size = System::Drawing::Size(265, 36);
			this->login->TabIndex = 5;
			this->login->Text = L"Login";
			this->login->TextImageRelation = System::Windows::Forms::TextImageRelation::TextAboveImage;
			this->login->UseVisualStyleBackColor = false;
			this->login->Click += gcnew System::EventHandler(this, &myUI::button1_Click);
			// 
			// password
			// 
			this->password->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(49)));
			this->password->BorderStyle = System::Windows::Forms::BorderStyle::None;
			this->password->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->password->ForeColor = System::Drawing::SystemColors::MenuHighlight;
			this->password->HideSelection = false;
			this->password->Location = System::Drawing::Point(87, 263);
			this->password->Name = L"password";
			this->password->ShortcutsEnabled = false;
			this->password->Size = System::Drawing::Size(163, 14);
			this->password->TabIndex = 7;
			this->password->TabStop = false;
			this->password->Text = L"Password";
			this->password->Click += gcnew System::EventHandler(this, &myUI::password_click);
			this->password->TextChanged += gcnew System::EventHandler(this, &myUI::password_TextChanged);
			
			// 
			// tableLayoutPanel1
			// 
			this->tableLayoutPanel1->BackColor = System::Drawing::Color::White;
			this->tableLayoutPanel1->ColumnCount = 2;
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel1->ForeColor = System::Drawing::Color::LavenderBlush;
			this->tableLayoutPanel1->Location = System::Drawing::Point(47, 228);
			this->tableLayoutPanel1->Name = L"tableLayoutPanel1";
			this->tableLayoutPanel1->RowCount = 2;
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel1->Size = System::Drawing::Size(264, 2);
			this->tableLayoutPanel1->TabIndex = 8;
			this->tableLayoutPanel1->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &myUI::tableLayoutPanel1_Paint);
			// 
			// tableLayoutPanel2
			// 
			this->tableLayoutPanel2->BackColor = System::Drawing::Color::White;
			this->tableLayoutPanel2->ColumnCount = 2;
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ColumnStyles->Add((gcnew System::Windows::Forms::ColumnStyle(System::Windows::Forms::SizeType::Percent,
				50)));
			this->tableLayoutPanel2->ForeColor = System::Drawing::Color::LavenderBlush;
			this->tableLayoutPanel2->Location = System::Drawing::Point(47, 281);
			this->tableLayoutPanel2->Name = L"tableLayoutPanel2";
			this->tableLayoutPanel2->RowCount = 2;
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->RowStyles->Add((gcnew System::Windows::Forms::RowStyle(System::Windows::Forms::SizeType::Percent, 50)));
			this->tableLayoutPanel2->Size = System::Drawing::Size(265, 2);
			this->tableLayoutPanel2->TabIndex = 9;
			this->tableLayoutPanel2->Paint += gcnew System::Windows::Forms::PaintEventHandler(this, &myUI::tableLayoutPanel2_Paint);
			// 
			// exit
			// 
			this->exit->BackColor = System::Drawing::Color::Transparent;
			this->exit->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->exit->ForeColor = System::Drawing::Color::Transparent;
			this->exit->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"exit.Image")));
			this->exit->ImageAlign = System::Drawing::ContentAlignment::BottomLeft;
			this->exit->Location = System::Drawing::Point(12, -83);
			this->exit->Name = L"exit";
			this->exit->Size = System::Drawing::Size(310, 71);
			this->exit->TabIndex = 11;
			this->exit->UseMnemonic = false;
			this->exit->UseVisualStyleBackColor = false;
			this->exit->Click += gcnew System::EventHandler(this, &myUI::exit_Click);
			// 
			// regis
			// 
			this->regis->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->regis->Font = (gcnew System::Drawing::Font(L"Modern No. 20", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->regis->ForeColor = System::Drawing::Color::FloralWhite;
			this->regis->Location = System::Drawing::Point(47, 402);
			this->regis->Name = L"regis";
			this->regis->Size = System::Drawing::Size(264, 35);
			this->regis->TabIndex = 12;
			this->regis->Text = L"Register";
			this->regis->UseVisualStyleBackColor = false;
			this->regis->Click += gcnew System::EventHandler(this, &myUI::newId_Click);
			// 
			// exiButton
			// 
			this->exiButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			this->exiButton->ForeColor = System::Drawing::Color::FloralWhite;
			this->exiButton->Image = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"exiButton.Image")));
			this->exiButton->Location = System::Drawing::Point(345, 1);
			this->exiButton->Name = L"exiButton";
			this->exiButton->Size = System::Drawing::Size(24, 24);
			this->exiButton->TabIndex = 13;
			this->exiButton->UseVisualStyleBackColor = false;
			// 
			// myUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(25)), static_cast<System::Int32>(static_cast<System::Byte>(36)),
				static_cast<System::Int32>(static_cast<System::Byte>(49)));
			this->ClientSize = System::Drawing::Size(372, 468);
			this->ControlBox = false;
			this->Controls->Add(this->exiButton);
			this->Controls->Add(this->regis);
			this->Controls->Add(this->exit);
			this->Controls->Add(this->tableLayoutPanel2);
			this->Controls->Add(this->tableLayoutPanel1);
			this->Controls->Add(this->password);
			this->Controls->Add(this->login);
			this->Controls->Add(this->userName);
			this->Controls->Add(this->pictureBox3);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->ForeColor = System::Drawing::Color::Olive;
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"myUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"Login";
			this->Load += gcnew System::EventHandler(this, &myUI::myUI_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox2))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pictureBox3))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) {
	}
private: System::Void textBox1_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void pictureBox2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void pictureBox3_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void myUI_Load(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void textBox2_TextChanged(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void tableLayoutPanel1_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void tableLayoutPanel2_Paint(System::Object^  sender, System::Windows::Forms::PaintEventArgs^  e) {
}
private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void pictureBox4_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void exit_Click(System::Object^  sender, System::EventArgs^  e) {

	
}
private: System::Void newId_Click(System::Object^  sender, System::EventArgs^  e) {
}
private: System::Void password_TextChanged(System::Object^  sender, System::EventArgs^  e) {

	
	this->password->PasswordChar = '*';

}
private: System::Void password_click(System::Object^  sender, System::EventArgs^  e) {

	
	 if(!this->passpress)
		this->password->Clear();
	 passpress++;

}
		


};
}
