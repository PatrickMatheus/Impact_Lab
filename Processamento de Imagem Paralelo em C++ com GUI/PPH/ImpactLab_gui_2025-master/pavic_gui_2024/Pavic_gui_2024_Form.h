#pragma once

namespace pavicgui2024 {
//#include "include/Diagnostic.h"



	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Threading;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace std; // Assuming Diagnostics is in the std namespace

	/// <summary>
	/// Summary for Pavic_gui_2024_Form
	/// </summary>
	public ref class Pavic_gui_2024_Form : public System::Windows::Forms::Form
	{
	public:
		Pavic_gui_2024_Form(void)
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
		~Pavic_gui_2024_Form()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ bt_open;
	protected:
	private: System::Windows::Forms::Button^ bt_close;
	private: System::Windows::Forms::Button^ bt_exit;
	private: System::Windows::Forms::PictureBox^ pbox_input;
	private: System::Windows::Forms::PictureBox^ pbox_copy;
	private: System::Windows::Forms::PictureBox^ pbox_output;
	private: System::Windows::Forms::Button^ bt_copy;
	private: System::Windows::Forms::Button^ bt_filter_bw;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Button^ bt_close_copy;
	private: System::Windows::Forms::Button^ bt_close_output;

	private: System::Windows::Forms::Label^ label11;
	private: System::Windows::Forms::Label^ label12;
	private: System::Diagnostics::Stopwatch^ copyStopwatch;
	private: System::Diagnostics::Stopwatch^ filterStopwatch;
	private: System::Windows::Forms::Button^ bt_filter_Sepia;
	private: System::Windows::Forms::Button^ bt_filter_Sepia_MultiThread;
	private: System::Windows::Forms::Button^ apply_filters;
	private: System::Windows::Forms::Button^ button1;



	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

		ref class SepiaThreadData {
		public:
			unsigned char* pIn;
			unsigned char* pOut;
			int strideIn;
			int strideOut;
			int width;
			int yStart;
			int yEnd;

			SepiaThreadData(unsigned char* _pIn, unsigned char* _pOut, int _strideIn, int _strideOut, int _width, int _start, int _end) {
				pIn = _pIn;
				pOut = _pOut;
				strideIn = _strideIn;
				strideOut = _strideOut;
				width = _width;
				yStart = _start;
				yEnd = _end;
			}

			void Run() {
				for (int y = yStart; y < yEnd ; y++) {
					unsigned char* rowIn = pIn + y * strideIn;
					unsigned char* rowOut = pOut + y * strideOut;

					for (int x = 0; x <  width; ++x) {
						int b = rowIn[x * 3];
						int g = rowIn[x * 3 + 1];
						int r = rowIn[x * 3 + 2];

						int tr = (int)(0.393 * r + 0.769 * g + 0.189 * b);
						int tg = (int)(0.349 * r + 0.686 * g + 0.168 * b);
						int tb = (int)(0.272 * r + 0.534 * g + 0.131 * b);

						rowOut[x * 3] = (unsigned char)(tb > 255 ? 255 : tb);
						rowOut[x * 3 + 1] = (unsigned char)(tg > 255 ? 255 : tg);
						rowOut[x * 3 + 2] = (unsigned char)(tr > 255 ? 255 : tr);
					}
				}
			}
		};

		ref class BlackWhiteThreadData_V {
		public:
			unsigned char* pIn;
			unsigned char* pOut;
			int strideIn;
			int strideOut;
			int height;
			int xStart;
			int xEnd;

			BlackWhiteThreadData_V(unsigned char* _pIn, unsigned char* _pOut, int _strideIn, int _strideOut, int _height, int _start, int _end) {
				pIn = _pIn;
				pOut = _pOut;
				strideIn = _strideIn;
				strideOut = _strideOut;
				height = _height;
				xStart = _start;
				xEnd = _end;
			}

			void Run() {
				for (int y = 0 ; y < height ; y++) {
					unsigned char* rowIn = pIn + y * strideIn;
					unsigned char* rowOut = pOut + y * strideOut;

					for (int x = xStart; x < xEnd; ++x) {
						int b = rowIn[x * 3];
						int g = rowIn[x * 3 + 1];
						int r = rowIn[x * 3 + 2];

						int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);

						rowOut[x * 3] = (unsigned char)(gray > 255 ? 255 : gray);
						rowOut[x * 3 + 1] = (unsigned char)(gray > 255 ? 255 : gray);
						rowOut[x * 3 + 2] = (unsigned char)(gray > 255 ? 255 : gray);
					}
				}
				
			}

		};


		ref class SepiaThreadData_V {
		public:
			unsigned char* pIn;
			unsigned char* pOut;
			int strideIn;
			int strideOut;
			int height;
			int xStart;
			int xEnd;

			SepiaThreadData_V(unsigned char* _pIn, unsigned char* _pOut, int _strideIn, int _strideOut, int _height, int _start, int _end) {
				pIn = _pIn;
				pOut = _pOut;
				strideIn = _strideIn;
				strideOut = _strideOut;
				height = _height;
				xStart = _start;
				xEnd = _end;
			}

			void Run() {
				for (int y = 0; y < height; y++) {
					unsigned char* rowIn = pIn + y * strideIn;
					unsigned char* rowOut = pOut + y * strideOut;

					for (int x = xStart; x < xEnd; ++x) {
						int b = rowIn[x * 3];
						int g = rowIn[x * 3 + 1];
						int r = rowIn[x * 3 + 2];

						int tr = (int)(0.393 * r + 0.769 * g + 0.189 * b);
						int tg = (int)(0.349 * r + 0.686 * g + 0.168 * b);
						int tb = (int)(0.272 * r + 0.534 * g + 0.131 * b);

						rowOut[x * 3] = (unsigned char)(tb > 255 ? 255 : tb);
						rowOut[x * 3 + 1] = (unsigned char)(tg > 255 ? 255 : tg);
						rowOut[x * 3 + 2] = (unsigned char)(tr > 255 ? 255 : tr);
					}
				}
			}
		};

		ref class BlackWhiteThreadData_H {
		public:
			unsigned char* pIn;
			unsigned char* pOut;
			int strideIn;
			int strideOut;
			int width;
			int yStart;
			int yEnd;

			BlackWhiteThreadData_H(unsigned char* _pIn, unsigned char* _pOut, int _strideIn, int _strideOut, int _width, int _start, int _end) {
				pIn = _pIn;
				pOut = _pOut;
				strideIn = _strideIn;
				strideOut = _strideOut;
				width = _width;
				yStart = _start;
				yEnd = _end;
			}

			void Run() {
				for (int y = yStart; y < yEnd; y++) {
					unsigned char* rowIn = pIn + y * strideIn;
					unsigned char* rowOut = pOut + y * strideOut;

					for (int x = 0; x < width; ++x) {
						int b = rowIn[x * 3];
						int g = rowIn[x * 3 + 1];
						int r = rowIn[x * 3 + 2];

						int gray = (int)(0.299 * r + 0.587 * g + 0.114 * b);

						rowOut[x * 3] = (unsigned char)(gray > 255 ? 255 : gray);
						rowOut[x * 3 + 1] = (unsigned char)(gray > 255 ? 255 : gray);
						rowOut[x * 3 + 2] = (unsigned char)(gray > 255 ? 255 : gray);
					}
				}

			}

		};


		ref class SepiaThreadData_H {
		public:
			unsigned char* pIn;
			unsigned char* pOut;
			int strideIn;
			int strideOut;
			int widht;
			int yStart;
			int yEnd;

			SepiaThreadData_H(unsigned char* _pIn, unsigned char* _pOut, int _strideIn, int _strideOut, int _widht, int _start, int _end) {
				pIn = _pIn;
				pOut = _pOut;
				strideIn = _strideIn;
				strideOut = _strideOut;
				widht = _widht;
				yStart = _start;
				yEnd = _end;
			}

			void Run() {
				for (int y = yStart; y < yEnd; y++) {
					unsigned char* rowIn = pIn + y * strideIn;
					unsigned char* rowOut = pOut + y * strideOut;

					for (int x = 0; x < widht; ++x) {
						int b = rowIn[x * 3];
						int g = rowIn[x * 3 + 1];
						int r = rowIn[x * 3 + 2];

						int tr = (int)(0.393 * r + 0.769 * g + 0.189 * b);
						int tg = (int)(0.349 * r + 0.686 * g + 0.168 * b);
						int tb = (int)(0.272 * r + 0.534 * g + 0.131 * b);

						rowOut[x * 3] = (unsigned char)(tb > 255 ? 255 : tb);
						rowOut[x * 3 + 1] = (unsigned char)(tg > 255 ? 255 : tg);
						rowOut[x * 3 + 2] = (unsigned char)(tr > 255 ? 255 : tr);
					}
				}
			}
		};

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->bt_open = (gcnew System::Windows::Forms::Button());
			this->bt_close = (gcnew System::Windows::Forms::Button());
			this->bt_exit = (gcnew System::Windows::Forms::Button());
			this->pbox_input = (gcnew System::Windows::Forms::PictureBox());
			this->pbox_copy = (gcnew System::Windows::Forms::PictureBox());
			this->pbox_output = (gcnew System::Windows::Forms::PictureBox());
			this->bt_copy = (gcnew System::Windows::Forms::Button());
			this->bt_filter_bw = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->bt_close_copy = (gcnew System::Windows::Forms::Button());
			this->bt_close_output = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia = (gcnew System::Windows::Forms::Button());
			this->bt_filter_Sepia_MultiThread = (gcnew System::Windows::Forms::Button());
			this->apply_filters = (gcnew System::Windows::Forms::Button());
			this->button1 = (gcnew System::Windows::Forms::Button());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_input))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_copy))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_output))->BeginInit();
			this->SuspendLayout();
			// 
			// bt_open
			// 
			this->bt_open->Location = System::Drawing::Point(9, 10);
			this->bt_open->Margin = System::Windows::Forms::Padding(2);
			this->bt_open->Name = L"bt_open";
			this->bt_open->Size = System::Drawing::Size(142, 37);
			this->bt_open->TabIndex = 0;
			this->bt_open->Text = L"Open";
			this->bt_open->UseVisualStyleBackColor = true;
			this->bt_open->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_open_Click);
			// 
			// bt_close
			// 
			this->bt_close->Location = System::Drawing::Point(291, 192);
			this->bt_close->Margin = System::Windows::Forms::Padding(2);
			this->bt_close->Name = L"bt_close";
			this->bt_close->Size = System::Drawing::Size(95, 28);
			this->bt_close->TabIndex = 1;
			this->bt_close->Text = L"Close";
			this->bt_close->UseVisualStyleBackColor = true;
			this->bt_close->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_Click);
			// 
			// bt_exit
			// 
			this->bt_exit->Location = System::Drawing::Point(9, 93);
			this->bt_exit->Margin = System::Windows::Forms::Padding(2);
			this->bt_exit->Name = L"bt_exit";
			this->bt_exit->Size = System::Drawing::Size(142, 37);
			this->bt_exit->TabIndex = 2;
			this->bt_exit->Text = L"Exit";
			this->bt_exit->UseVisualStyleBackColor = true;
			this->bt_exit->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_exit_Click);
			// 
			// pbox_input
			// 
			this->pbox_input->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_input->Location = System::Drawing::Point(13, 225);
			this->pbox_input->Margin = System::Windows::Forms::Padding(2);
			this->pbox_input->Name = L"pbox_input";
			this->pbox_input->Size = System::Drawing::Size(374, 331);
			this->pbox_input->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_input->TabIndex = 3;
			this->pbox_input->TabStop = false;
			this->pbox_input->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::pbox_input_Click);
			// 
			// pbox_copy
			// 
			this->pbox_copy->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_copy->Location = System::Drawing::Point(416, 225);
			this->pbox_copy->Margin = System::Windows::Forms::Padding(2);
			this->pbox_copy->Name = L"pbox_copy";
			this->pbox_copy->Size = System::Drawing::Size(374, 331);
			this->pbox_copy->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_copy->TabIndex = 4;
			this->pbox_copy->TabStop = false;
			// 
			// pbox_output
			// 
			this->pbox_output->BorderStyle = System::Windows::Forms::BorderStyle::Fixed3D;
			this->pbox_output->Location = System::Drawing::Point(815, 225);
			this->pbox_output->Margin = System::Windows::Forms::Padding(2);
			this->pbox_output->Name = L"pbox_output";
			this->pbox_output->Size = System::Drawing::Size(374, 331);
			this->pbox_output->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pbox_output->TabIndex = 5;
			this->pbox_output->TabStop = false;
			// 
			// bt_copy
			// 
			this->bt_copy->Location = System::Drawing::Point(9, 51);
			this->bt_copy->Margin = System::Windows::Forms::Padding(2);
			this->bt_copy->Name = L"bt_copy";
			this->bt_copy->Size = System::Drawing::Size(142, 37);
			this->bt_copy->TabIndex = 6;
			this->bt_copy->Text = L"Copy";
			this->bt_copy->UseVisualStyleBackColor = true;
			this->bt_copy->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_copy_Click);
			// 
			// bt_filter_bw
			// 
			this->bt_filter_bw->Location = System::Drawing::Point(216, 11);
			this->bt_filter_bw->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_bw->Name = L"bt_filter_bw";
			this->bt_filter_bw->Size = System::Drawing::Size(142, 37);
			this->bt_filter_bw->TabIndex = 7;
			this->bt_filter_bw->Text = L"Filter BW";
			this->bt_filter_bw->UseVisualStyleBackColor = true;
			this->bt_filter_bw->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_bw_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(1078, 576);
			this->label1->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(128, 13);
			this->label1->TabIndex = 8;
			this->label1->Text = L" Antonio Souto Rodriguez";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(7, 576);
			this->label2->Margin = System::Windows::Forms::Padding(2, 0, 2, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(94, 13);
			this->label2->TabIndex = 9;
			this->label2->Text = L" PAVIC LAB: 2024";
			// 
			// bt_close_copy
			// 
			this->bt_close_copy->Location = System::Drawing::Point(694, 192);
			this->bt_close_copy->Margin = System::Windows::Forms::Padding(2);
			this->bt_close_copy->Name = L"bt_close_copy";
			this->bt_close_copy->Size = System::Drawing::Size(95, 28);
			this->bt_close_copy->TabIndex = 10;
			this->bt_close_copy->Text = L"Close";
			this->bt_close_copy->UseVisualStyleBackColor = true;
			this->bt_close_copy->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_copy_Click);
			// 
			// bt_close_output
			// 
			this->bt_close_output->Location = System::Drawing::Point(1094, 192);
			this->bt_close_output->Margin = System::Windows::Forms::Padding(2);
			this->bt_close_output->Name = L"bt_close_output";
			this->bt_close_output->Size = System::Drawing::Size(95, 28);
			this->bt_close_output->TabIndex = 11;
			this->bt_close_output->Text = L"Close";
			this->bt_close_output->UseVisualStyleBackColor = true;
			this->bt_close_output->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_close_output_Click);
			// 
			// bt_filter_Sepia
			// 
			this->bt_filter_Sepia->Location = System::Drawing::Point(216, 52);
			this->bt_filter_Sepia->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia->Name = L"bt_filter_Sepia";
			this->bt_filter_Sepia->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia->TabIndex = 12;
			this->bt_filter_Sepia->Text = L"Filter Sepia";
			this->bt_filter_Sepia->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_Click);
			// 
			// bt_filter_Sepia_MultiThread
			// 
			this->bt_filter_Sepia_MultiThread->Location = System::Drawing::Point(216, 93);
			this->bt_filter_Sepia_MultiThread->Margin = System::Windows::Forms::Padding(2);
			this->bt_filter_Sepia_MultiThread->Name = L"bt_filter_Sepia_MultiThread";
			this->bt_filter_Sepia_MultiThread->Size = System::Drawing::Size(142, 37);
			this->bt_filter_Sepia_MultiThread->TabIndex = 13;
			this->bt_filter_Sepia_MultiThread->Text = L"Filter Sepia MultiThread";
			this->bt_filter_Sepia_MultiThread->UseVisualStyleBackColor = true;
			this->bt_filter_Sepia_MultiThread->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::bt_filter_Sepia_MultiThread_Click);
			// 
			// apply_filters
			// 
			this->apply_filters->Location = System::Drawing::Point(416, 11);
			this->apply_filters->Margin = System::Windows::Forms::Padding(2);
			this->apply_filters->Name = L"apply_filters";
			this->apply_filters->Size = System::Drawing::Size(142, 37);
			this->apply_filters->TabIndex = 14;
			this->apply_filters->Text = L"Filters MultiThread_V";
			this->apply_filters->UseVisualStyleBackColor = true;
			this->apply_filters->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::button1_Click_1);
			// 
			// button1
			// 
			this->button1->Location = System::Drawing::Point(416, 52);
			this->button1->Margin = System::Windows::Forms::Padding(2);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(142, 37);
			this->button1->TabIndex = 15;
			this->button1->Text = L"Filters MultiThread_H";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::button1_Click_2);
			// 
			// Pavic_gui_2024_Form
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1254, 625);
			this->Controls->Add(this->button1);
			this->Controls->Add(this->apply_filters);
			this->Controls->Add(this->bt_filter_Sepia_MultiThread);
			this->Controls->Add(this->bt_filter_Sepia);
			this->Controls->Add(this->bt_close_output);
			this->Controls->Add(this->bt_close_copy);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->bt_filter_bw);
			this->Controls->Add(this->bt_copy);
			this->Controls->Add(this->pbox_output);
			this->Controls->Add(this->pbox_copy);
			this->Controls->Add(this->pbox_input);
			this->Controls->Add(this->bt_exit);
			this->Controls->Add(this->bt_close);
			this->Controls->Add(this->bt_open);
			this->Margin = System::Windows::Forms::Padding(2);
			this->Name = L"Pavic_gui_2024_Form";
			this->Text = L"PROJECT: IMPACTLAB LAB 2025";
			this->Load += gcnew System::EventHandler(this, &Pavic_gui_2024_Form::Pavic_gui_2024_Form_Load);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_input))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_copy))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pbox_output))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void bt_open_Click(System::Object^ sender, System::EventArgs^ e) {
		OpenFileDialog^ ofd = gcnew OpenFileDialog();
		if (ofd->ShowDialog() == System::Windows::Forms::DialogResult::OK) {
			pbox_input->ImageLocation = ofd->FileName;
		}
	}
private: System::Void bt_close_Click(System::Object^ sender, System::EventArgs^ e) {

	pbox_input->Image = nullptr;

	
}
private: System::Void bt_copy_Click(System::Object^ sender, System::EventArgs^ e) {
	//copyStopwatch = gcnew System::Diagnostics.Stopwatch();
	//copyStopwatch->Start();
	pbox_copy->Image = pbox_input->Image;

	//copyStopwatch->Stop();
	//label11->Text = "Tempo de cópia: " + copyStopwatch->ElapsedMilliseconds.ToString() + " ms";

}
private: System::Void bt_filter_bw_Click(System::Object^ sender, System::EventArgs^ e) {

	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	for (int i = 0; i < inputImage->Width; i++) {
		for (int j = 0; j < inputImage->Height; j++) {
			Color pixelColor = inputImage->GetPixel(i, j);
			int grayValue = (int)(0.299 * pixelColor.R + 0.587 * pixelColor.G + 0.114 * pixelColor.B);
			outputImage->SetPixel(i, j, Color::FromArgb(grayValue, grayValue, grayValue));
		}
	}

	// Display the output image
	pbox_output->Image = outputImage;
}
private: System::Void bt_exit_Click(System::Object^ sender, System::EventArgs^ e) {
	Application::Exit();
}
private: System::Void bt_close_copy_Click(System::Object^ sender, System::EventArgs^ e) {
	pbox_copy->Image = nullptr;
	
}
private: System::Void bt_close_output_Click(System::Object^ sender, System::EventArgs^ e) {
	pbox_output->Image = nullptr;
}
private: System::Void Pavic_gui_2024_Form_Load(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void pbox_input_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void bt_filter_Sepia_Click(System::Object^ sender, System::EventArgs^ e) {
	// Get the input image
	Bitmap^ inputImage = (Bitmap^)pbox_input->Image;

	// Create a new output image with the same dimensions
	Bitmap^ outputImage = gcnew Bitmap(inputImage->Width, inputImage->Height);

	// Apply the black and white filter
	for (int i = 0; i < inputImage->Width; i++) {
		for (int j = 0; j < inputImage->Height; j++) {
			// Step:1 Get the color of the current pixel
			Color pixelColor = inputImage->GetPixel(i, j);

			// Step : 2  Extract original Red, Green, annd Blue Values
			int r = pixelColor.R;
			int g = pixelColor.G;
			int b = pixelColor.B;
			// Step: 3 Calculate the new pixel values using Sepia Formula
			/*	tr = 0.393R + 0.769G + 0.189B
				tg = 0.349R + 0.686G + 0.168B
				tb = 0.272R + 0.534G + 0.131B
				*/
			double tr = 0.393*r + 0.769*g + 0.189*b;
			double tg = 0.349 * r + 0.686 * g + 0.168 * b;
			double tb = 0.272 * r + 0.534 * g + 0.131*b;

			// Step : 4 Clamp the values  0- 255 range 
			int newR = Math::Min(255, (int)tr);
			int newG = Math::Min(255, (int)tg);
			int newB = Math::Min(255, (int)tb);

			//outputImage->SetPixel(i, j, Color::FromArgb(tr, tg, tb));
			outputImage->SetPixel(i, j, Color::FromArgb(newR, newG, newB));

			/*	tr = 0.393R + 0.769G + 0.189B
				tg = 0.349R + 0.686G + 0.168B
				tb = 0.272R + 0.534G + 0.131B*/

		}
	}

	// Display the output image
	pbox_output->Image = outputImage;
}
private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
}
private: System::Void bt_filter_Sepia_MultiThread_Click(System::Object^ sender, System::EventArgs^ e) {
	if (pbox_input->Image == nullptr) return;

	Bitmap^ inputImage = gcnew Bitmap(pbox_input->Image);
	int width = inputImage->Width;
	int height = inputImage->Height;
	Bitmap^ outputImage = gcnew Bitmap(width, height, PixelFormat::Format24bppRgb);

	Rectangle rect = Rectangle(0, 0, width, height);
	BitmapData^ inputData = inputImage->LockBits(rect, ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
	BitmapData^ outputData = outputImage->LockBits(rect, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);

	unsigned char* pIn = (unsigned char*)(void*)inputData->Scan0;
	unsigned char* pOut = (unsigned char*)(void*)outputData->Scan0;
	int strideIn = inputData->Stride;
	int strideOut = outputData->Stride;
	int midY = height / 2;

	SepiaThreadData^ data1 = gcnew SepiaThreadData(pIn, pOut, strideIn, strideOut, width, 0, midY);
	SepiaThreadData^ data2 = gcnew SepiaThreadData(pIn, pOut, strideIn, strideOut, width, midY, height);

	Thread^ t1 = gcnew Thread(gcnew ThreadStart(data1, &SepiaThreadData::Run));
	Thread^ t2 = gcnew Thread(gcnew ThreadStart(data2, &SepiaThreadData::Run));
	t1->Start();
	t2->Start();
	t1->Join();
	t2->Join();

	inputImage->UnlockBits(inputData);
	outputImage->UnlockBits(outputData);
	pbox_output->Image = outputImage;

}
private: System::Void button1_Click_1(System::Object^ sender, System::EventArgs^ e) {
	if (pbox_input->Image == nullptr) return;

	Bitmap^ inputImage = gcnew Bitmap(pbox_input->Image);
	int width = inputImage->Width;
	int height = inputImage->Height;
	Bitmap^ outputImage = gcnew Bitmap(width, height, PixelFormat::Format24bppRgb);

	Rectangle rect = Rectangle(0, 0, width, height);
	BitmapData^ inputData = inputImage->LockBits(rect, ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
	BitmapData^ outputData = outputImage->LockBits(rect, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);

	unsigned char* pIn = (unsigned char*)(void*)inputData->Scan0;
	unsigned char* pOut = (unsigned char*)(void*)outputData->Scan0;
	int strideIn = inputData->Stride;
	int strideOut = outputData->Stride;
	int midY = height / 2;
	int midX = width / 2;

	BlackWhiteThreadData_V^ data1 = gcnew BlackWhiteThreadData_V(pIn, pOut, strideIn, strideOut, height, 0, midX);
	SepiaThreadData_V^ data2 = gcnew SepiaThreadData_V(pIn, pOut, strideIn, strideOut, height, midX, width);

	Thread^ t1 = gcnew Thread(gcnew ThreadStart(data1, &BlackWhiteThreadData_V::Run));
	Thread^ t2 = gcnew Thread(gcnew ThreadStart(data2, &SepiaThreadData_V::Run));
	t1->Start();
	t2->Start();
	t1->Join();
	t2->Join();

	inputImage->UnlockBits(inputData);
	outputImage->UnlockBits(outputData);
	pbox_output->Image = outputImage;
}
private: System::Void button1_Click_2(System::Object^ sender, System::EventArgs^ e) {
	if (pbox_input->Image == nullptr) return;

	Bitmap^ inputImage = gcnew Bitmap(pbox_input->Image);
	int width = inputImage->Width;
	int height = inputImage->Height;
	Bitmap^ outputImage = gcnew Bitmap(width, height, PixelFormat::Format24bppRgb);

	Rectangle rect = Rectangle(0, 0, width, height);
	BitmapData^ inputData = inputImage->LockBits(rect, ImageLockMode::ReadOnly, PixelFormat::Format24bppRgb);
	BitmapData^ outputData = outputImage->LockBits(rect, ImageLockMode::WriteOnly, PixelFormat::Format24bppRgb);

	unsigned char* pIn = (unsigned char*)(void*)inputData->Scan0;
	unsigned char* pOut = (unsigned char*)(void*)outputData->Scan0;
	int strideIn = inputData->Stride;
	int strideOut = outputData->Stride;
	int midY = height / 2;
	int midX = width / 2;

	BlackWhiteThreadData_H^ data1 = gcnew BlackWhiteThreadData_H(pIn, pOut, strideIn, strideOut, width, 0, midY);
	SepiaThreadData_H^ data2 = gcnew SepiaThreadData_H(pIn, pOut, strideIn, strideOut, width, midY, height);

	Thread^ t1 = gcnew Thread(gcnew ThreadStart(data1, &BlackWhiteThreadData_H::Run));
	Thread^ t2 = gcnew Thread(gcnew ThreadStart(data2, &SepiaThreadData_H::Run));
	t1->Start();
	t2->Start();
	t1->Join();
	t2->Join();

	inputImage->UnlockBits(inputData);
	outputImage->UnlockBits(outputData);
	pbox_output->Image = outputImage;
}
};
}
