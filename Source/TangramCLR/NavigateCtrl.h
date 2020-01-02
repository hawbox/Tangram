#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;


namespace TangramCLR {

	/// <summary>
	/// Summary for NavigateCtrl
	/// </summary>
	public ref class NavigateCtrl : public System::Windows::Forms::UserControl
	{
	public:
		NavigateCtrl(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			hostnode = nullptr;
			bindnode = nullptr;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~NavigateCtrl()
		{
			if (components)
			{
				delete components;
			}
		}
	private: WndNode^ hostnode;
	private: WndNode^ bindnode;
	private: System::Windows::Forms::TreeView^ NavigateTreeView;
	protected:

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
			this->NavigateTreeView = (gcnew System::Windows::Forms::TreeView());
			this->SuspendLayout();
			// 
			// NavigateTreeView
			// 
			this->NavigateTreeView->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(255)),
				static_cast<System::Int32>(static_cast<System::Byte>(192)), static_cast<System::Int32>(static_cast<System::Byte>(192)));
			this->NavigateTreeView->Dock = System::Windows::Forms::DockStyle::Fill;
			this->NavigateTreeView->Font = (gcnew System::Drawing::Font(L"Times New Roman", 12, System::Drawing::FontStyle::Bold));
			this->NavigateTreeView->FullRowSelect = true;
			this->NavigateTreeView->HideSelection = false;
			this->NavigateTreeView->HotTracking = true;
			this->NavigateTreeView->Location = System::Drawing::Point(0, 0);
			this->NavigateTreeView->Name = L"NavigateTreeView";
			this->NavigateTreeView->ShowNodeToolTips = true;
			this->NavigateTreeView->Size = System::Drawing::Size(385, 470);
			this->NavigateTreeView->TabIndex = 0;
			this->NavigateTreeView->AfterSelect += gcnew System::Windows::Forms::TreeViewEventHandler(this, &NavigateCtrl::NavigateTreeView_AfterSelect);
			this->NavigateTreeView->NodeMouseClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &NavigateCtrl::NavigateTreeView_NodeMouseClick);
			this->NavigateTreeView->NodeMouseDoubleClick += gcnew System::Windows::Forms::TreeNodeMouseClickEventHandler(this, &NavigateCtrl::NavigateTreeView_NodeMouseDoubleClick);
			// 
			// NavigateCtrl
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(12, 25);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->Controls->Add(this->NavigateTreeView);
			this->Name = L"NavigateCtrl";
			this->Size = System::Drawing::Size(385, 470);
			this->Load += gcnew System::EventHandler(this, &NavigateCtrl::NavigateCtrl_Load);
			this->ResumeLayout(false);

		}
#pragma endregion
	private: System::Void LoadNode(TreeNode^ pNode, CTangramXmlParse* pParse);
	private: System::Void NavigateCtrl_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void NavigateTreeView_NodeMouseDoubleClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e);
	private: System::Void NavigateTreeView_NodeMouseClick(System::Object^ sender, System::Windows::Forms::TreeNodeMouseClickEventArgs^ e);
	private: System::Void NavigateTreeView_AfterSelect(System::Object^ sender, System::Windows::Forms::TreeViewEventArgs^ e);
	};
}
