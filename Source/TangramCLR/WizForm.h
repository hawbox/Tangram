#pragma once

namespace TangramCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WizForm
	/// </summary>
	public ref class WizForm : public System::Windows::Forms::Form
	{
	public:
		WizForm(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
		}

		property String^ NavigateData
		{
			void set(String^ strData);
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~WizForm()
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
			this->SuspendLayout();
			// 
			// WizForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(445, 229);
			this->Name = L"WizForm";
			this->Text = L"WizForm";
			this->Load += gcnew System::EventHandler(this, &WizForm::WizForm_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void WizForm_Load(System::Object^ sender, System::EventArgs^ e);
	};
}
