#include <wx/wx.h>
#include <wx/grid.h>
#include <vector>
#include <string>
#include <sqlite3.h> 
#include "utilities.h"
#include "FourthStepItem.h"
#include "SqlDB.h"

using namespace std;


class Simple : public wxFrame
{
public:
    Simple(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(350, 250))
	{
		wxMenu *menuFile = new wxMenu;
	    // menuFile->Append(1, "&New...\tCtrl-N",
	    //                  "New Twelve Step Options");
	    wxMenu *subMenu = new wxMenu; 
	    subMenu->Append(1, "&4th Step", "New 4th Step");
	    subMenu->Append(2, "&8th Step", "New 8th Step");
	    menuFile->AppendSubMenu(subMenu, "Steps");
	    menuFile->AppendSeparator();
	    menuFile->Append(wxID_EXIT);
	    wxMenu *menuHelp = new wxMenu;
	    menuHelp->Append(wxID_ABOUT);
	    wxMenuBar *menuBar = new wxMenuBar;
	    menuBar->Append( menuFile, "&File" );
	    menuBar->Append( menuHelp, "&Help" );
	    SetMenuBar( menuBar );
	    CreateStatusBar();
	    SetStatusText( "Twelve Step Helper!" );
		Centre();
	}

	private:
	    void OnFourth(wxCommandEvent& event);
	    void OnEighth(wxCommandEvent& event);
	    void OnExit(wxCommandEvent& event);
	    void OnAbout(wxCommandEvent& event);
	    void OnSaveFourth(wxCommandEvent& event);
	    wxDECLARE_EVENT_TABLE();
};

class Fourth : public wxFrame
{
public:
    Fourth(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(650, 550))
	{
		wxMenu *menuFile = new wxMenu;
	    menuFile->Append(1, "&New...\tCtrl-N",
	                     "New Fourth Step Log");
	    menuFile->Append(1, "&Save...\tCtrl-S",
	                     "Save Record");
	    menuFile->Append(wxID_EXIT);
	    wxMenuBar *menuBar = new wxMenuBar;
	    menuBar->Append( menuFile, "&File" );
	    SetMenuBar( menuBar );
	    CreateStatusBar();
		Centre();
	}

	private:
	    
};

class Eighth : public wxFrame
{
public:
    Eighth(const wxString& title)
		: wxFrame(NULL, wxID_ANY, title, wxDefaultPosition, wxSize(650, 550))
	{
		
		Centre();
	}
	void SaveFile();

	private:
	    
};




class MyApp : public wxApp
{
public:
	bool OnInit()
	{
		Simple *simple = new Simple(wxT("Twelve Step Helper"));
		simple->Show(true);
		return true;
	}
};

void Simple::OnFourth(wxCommandEvent& event)
{
    Fourth *simple = new Fourth(wxT("Fourth Step Info"));
    simple->Show(true);
	SqlDB db;
	db.OpenDB();
	db.CreateFourthStepTableIfNotExists();
	Records recs = db.RetrieveFourthStepInfo();
	std::vector<FourthStepItem> *v;
	for(int i = 0; i < recs.size(); i++) 
	{
		Record rec = recs[i];
		FourthStepItem *item = new FourthStepItem();
		item->set_person(rec[0]);
		item->set_the_cause(rec[1]);
		item->set_my_part(rec[2]);
		item->set_threat(rec[3]);
		v->push_back(*item);
	}
	wxGrid *grid = new wxGrid(simple, wxID_ANY);
	int grid_size = v->size();
	if(grid_size < 1) grid_size = 1;
    grid->CreateGrid(grid_size, 4);
    grid->SetColLabelValue(0, "Person With Whom We Are Angry");
    grid->SetColLabelValue(1, "The Cause");
    grid->SetColLabelValue(2, "Threatens");
    grid->SetColLabelValue(3, "My Part");
    grid->AutoSize();
	db.CloseDB();
	
}

void Simple::OnEighth(wxCommandEvent& event)
{
    Eighth *simple = new Eighth(wxT("Eighth Step Info"));
	simple->Show(true);
	SqlDB db;
	db.OpenDB();
}

void Simple::OnSaveFourth(wxCommandEvent& event)
{
	SqlDB db;
	db.OpenDB();
}

void Simple::OnAbout(wxCommandEvent& event)
{
    wxMessageBox( "This is a Twelve Step Helper Application. \n It will help you keep track of all of your twelve step work.",
                  "About Hello World", wxOK | wxICON_INFORMATION );
}

void Simple::OnExit(wxCommandEvent& event)
{
    Close( true );
}

wxBEGIN_EVENT_TABLE(Simple, wxFrame)
    EVT_MENU(1,   Simple::OnFourth)
    EVT_MENU(2,   Simple::OnEighth)
    EVT_MENU(3,   Simple::OnSaveFourth)
    EVT_MENU(wxID_EXIT,  Simple::OnExit)
    EVT_MENU(wxID_ABOUT, Simple::OnAbout)
wxEND_EVENT_TABLE()


wxIMPLEMENT_APP(MyApp);
