#pragma once

namespace Project5 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
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
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog1;
	protected:
	private: System::Windows::Forms::Button^  button1;
	private: System::Windows::Forms::Button^  SENDBUTTON;

	private: System::Windows::Forms::RichTextBox^  SENDBOX;
	private: System::Windows::Forms::RichTextBox^  RECEIVEBOX;
	private: System::Windows::Forms::RichTextBox^  FILEBOX;


	private:
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
			this->openFileDialog1 = (gcnew System::Windows::Forms::OpenFileDialog());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->SENDBUTTON = (gcnew System::Windows::Forms::Button());
			this->SENDBOX = (gcnew System::Windows::Forms::RichTextBox());
			this->RECEIVEBOX = (gcnew System::Windows::Forms::RichTextBox());
			this->FILEBOX = (gcnew System::Windows::Forms::RichTextBox());
			this->SuspendLayout();
			// 
			// openFileDialog1
			// 
			this->openFileDialog1->FileName = L"openFileDialog1";
			// 
			// button1
			// 
			this->button1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->button1->Location = System::Drawing::Point(627, 343);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(163, 36);
			this->button1->TabIndex = 0;
			this->button1->Text = L"SELECT FILES";
			this->button1->UseVisualStyleBackColor = false;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// SENDBUTTON
			// 
			this->SENDBUTTON->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)), static_cast<System::Int32>(static_cast<System::Byte>(192)),
				static_cast<System::Int32>(static_cast<System::Byte>(128)));
			this->SENDBUTTON->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 7.8F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SENDBUTTON->ForeColor = System::Drawing::SystemColors::Highlight;
			this->SENDBUTTON->Location = System::Drawing::Point(12, 335);
			this->SENDBUTTON->Name = L"SENDBUTTON";
			this->SENDBUTTON->Size = System::Drawing::Size(162, 53);
			this->SENDBUTTON->TabIndex = 1;
			this->SENDBUTTON->Text = L"SEND";
			this->SENDBUTTON->UseVisualStyleBackColor = false;
			this->SENDBUTTON->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// SENDBOX
			// 
			this->SENDBOX->Location = System::Drawing::Point(12, 63);
			this->SENDBOX->Name = L"SENDBOX";
			this->SENDBOX->Size = System::Drawing::Size(190, 242);
			this->SENDBOX->TabIndex = 2;
			this->SENDBOX->Text = L"";
			// 
			// RECEIVEBOX
			// 
			this->RECEIVEBOX->Location = System::Drawing::Point(235, 63);
			this->RECEIVEBOX->Name = L"RECEIVEBOX";
			this->RECEIVEBOX->Size = System::Drawing::Size(192, 242);
			this->RECEIVEBOX->TabIndex = 3;
			this->RECEIVEBOX->Text = L"";
			this->RECEIVEBOX->Text += "NO MESSAGES RECEIVED";
			// 
			// FILEBOX
			// 
			this->FILEBOX->Location = System::Drawing::Point(467, 272);
			this->FILEBOX->Name = L"FILEBOX";
			this->FILEBOX->Size = System::Drawing::Size(484, 48);
			this->FILEBOX->TabIndex = 4;
			this->FILEBOX->Text = L"";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::YellowGreen;
			this->ClientSize = System::Drawing::Size(963, 417);
			this->Controls->Add(this->FILEBOX);
			this->Controls->Add(this->RECEIVEBOX);
			this->Controls->Add(this->SENDBOX);
			this->Controls->Add(this->SENDBUTTON);
			this->Controls->Add(this->button1);
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void button1_Click(System::Object^  sender, System::EventArgs^  e) //SELECT BUTTON
	{
		String^ FILE;


		openFileDialog1->ShowDialog();
		FILE = openFileDialog1->FileName;
		this->FILEBOX->Text += FILE;
		




	}
	private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) //SNED BUTTON
	{
		String^ str;
		str = SENDBOX->Text;

		SENDBOX->Clear();
		




	}
			
};
}
