#pragma once
#include "LHerdaUtils.h"
namespace GUISemestralnapraca {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Hlavne_okno
	/// </summary>
	public ref class Hlavne_okno : public System::Windows::Forms::Form
	{
	private: System::Windows::Forms::Panel^ panelBottom;

	private: System::Windows::Forms::DataGridView^ dataGridViewFile;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ ColumnJobConditionNazov;
	private: System::Windows::Forms::DataGridView^ dataGridViewJobCondition;
	public:
		Hlavne_okno(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			dataGridViewValidator = gcnew LHerdaUtils::DataGridViewValidator(dataGridViewJobCondition, true);
			dataGridViewValidator->Add(ColumnJobConditionNazov, LHerdaUtils::Statics::DataGridViewCellValidatorNotNullCommon);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Hlavne_okno()
		{
			if (components)
			{
				delete components;
			}
		}

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
			this->panelBottom = (gcnew System::Windows::Forms::Panel());

			this->dataGridViewFile = (gcnew System::Windows::Forms::DataGridView());
			this->ColumnJobConditionNazov = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());

			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewFile))->BeginInit();
			System::Windows::Forms::DataGridViewCellStyle^ dataGridViewCellStyle7 = (gcnew System::Windows::Forms::DataGridViewCellStyle());

			this->panelBottom->SuspendLayout();

			// 
// dataGridViewFile
// 
			this->dataGridViewFile->AllowUserToAddRows = false;
			this->dataGridViewFile->AllowUserToDeleteRows = false;
			this->dataGridViewFile->AllowUserToOrderColumns = true;
			this->dataGridViewFile->AutoSizeColumnsMode = System::Windows::Forms::DataGridViewAutoSizeColumnsMode::Fill;
			this->dataGridViewFile->BackgroundColor = System::Drawing::SystemColors::Info;
			this->dataGridViewFile->ColumnHeadersBorderStyle = System::Windows::Forms::DataGridViewHeaderBorderStyle::Single;
			this->dataGridViewFile->ColumnHeadersHeight = 30;
			this->dataGridViewFile->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(1)
			{
				this->ColumnJobConditionNazov
			});
			this->dataGridViewFile->Dock = System::Windows::Forms::DockStyle::Fill;
			this->dataGridViewFile->EditMode = System::Windows::Forms::DataGridViewEditMode::EditOnEnter;
			this->dataGridViewFile->Location = System::Drawing::Point(0, 0);
			this->dataGridViewFile->Name = L"dataGridViewFile";
			this->dataGridViewFile->RowHeadersVisible = false;
			dataGridViewCellStyle7->BackColor = System::Drawing::SystemColors::Info;
			dataGridViewCellStyle7->ForeColor = System::Drawing::Color::Black;
			dataGridViewCellStyle7->SelectionBackColor = System::Drawing::Color::Aqua;
			dataGridViewCellStyle7->SelectionForeColor = System::Drawing::Color::Black;
			this->dataGridViewFile->RowsDefaultCellStyle = dataGridViewCellStyle7;
			this->dataGridViewFile->RowTemplate->Height = 26;
			this->dataGridViewFile->RowTemplate->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->dataGridViewFile->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->dataGridViewFile->Size = System::Drawing::Size(1117, 66);
			this->dataGridViewFile->TabIndex = 1;


			// 
			// panelBottom
			// 
			this->panelBottom->Controls->Add(this->dataGridViewFile);
			
			this->panelBottom->Location = System::Drawing::Point(0, 48);
			this->panelBottom->Name = L"panelBottom";
			this->panelBottom->Size = System::Drawing::Size(500, 500);
			this->panelBottom->TabIndex = 6;
			this->panelBottom->BackColor = System::Drawing::Color::Red;
			// 
			// ColumnJobConditionNazov
			// 
			this->ColumnJobConditionNazov->FillWeight = 150;
			this->ColumnJobConditionNazov->HeaderText = L"Názov";
			this->ColumnJobConditionNazov->Name = L"ColumnJobConditionNazov";
			this->ColumnJobConditionNazov->ToolTipText = L"Názov vytvorenej úlohy (jobu)";


			//
			// hlavne okno
			//
			this->components = gcnew System::ComponentModel::Container();
			this->Size = System::Drawing::Size(1550, 800);
			this->Text = L"Hlavne_okno";
			this->Padding = System::Windows::Forms::Padding(0);
			this->AutoScrollMinSize = System::Drawing::Size(992, 0);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			//
			//
			//
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridViewFile))->EndInit();
			this->Controls->Add(this->panelBottom);
			this->panelBottom->ResumeLayout(false);
		}
#pragma endregion
	private:
		LHerdaUtils::DataGridViewValidator^ dataGridViewValidator;
	};
	
}
