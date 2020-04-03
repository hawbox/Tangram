#pragma once

namespace TangramCLR {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Collections::Generic;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for WizForm
	/// </summary>
	public ref class WizForm : public System::Windows::Forms::Form
	{
	public:
		static int m_nProjectCount = 0;
		static bool m_bInitLibInfo = false;
		static bool m_bSolutionModel = false;
		String^ m_strAppType=L"";
		ListView^ m_pWizListView = nullptr;
		Dictionary<String^, Control^>^ m_pWizCtrlDic = gcnew Dictionary<String^, Control^>();

		WizForm(void);

		property String^ NavigateData
		{
			void set(String^ strData);
		}

		property String^ TemplateID
		{
			String^ get()
			{
				return m_strTemplateID;
			};
			void set(String^ strTemplateID)
			{
				m_strTemplateID = strTemplateID;
			};
		}
		
		property Dictionary<String^, Control^>^ WizCtrlDic
		{
			Dictionary<String^, Control^>^ get()
			{
				return m_pWizCtrlDic;
			};
		}

		void InitCustomizeDic(String^ strDicData);
		void FillListView(String^ strXmlData, System::Windows::Forms::ListView^ ctrl);

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
		String^ m_strTemplateID = nullptr;
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
