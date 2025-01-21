#ifndef Unit2H
#define Unit2H

#include <System.Classes.hpp>
#include <FMX.Controls.hpp>
#include <FMX.Forms.hpp>
#include <FMX.Controls.Presentation.hpp>
#include <FMX.StdCtrls.hpp>
#include <FMX.Types.hpp>
#include <FMX.Edit.hpp>
#include <FMX.Memo.hpp>
#include <FMX.Ani.hpp>
#include <FMX.Memo.Types.hpp>
#include <FMX.ScrollBox.hpp>
#include <map>
#include <vector>

//---------------------------------------------------------------------------

class TForm2 : public TForm
{
__published:
	TLabel *lblFunFact;
	TLabel *lblGreeting;
	TEdit *edtUserInput;
	TButton *funfactbutton;
	TMemo *Convo;
	TImageControl *ImageControl1;
    TPanel *panelProgress;
    TImageControl *ImageControl2;
    TColorAnimation *ColorAnimation1;
    TButton *Closebtn;
	TLabel *Label1;
	TLabel *Label2;


    void __fastcall FormCreate(TObject *Sender);
    void __fastcall btnSendClick(TObject *Sender);
    void __fastcall funfactbuttonClick(TObject *Sender);
    void __fastcall edtUserInputKeyDown(TObject *Sender, WORD &Key, TShiftState Shift);
    void __fastcall ClosebtnClick(TObject *Sender);

private:
	bool isGameActive;
	String currentGameMode;
	std::map<String, String> knowledgeBase;
	std::vector<String> typingSentences;
	TDateTime startTime;
	int currentSentenceLength;
	std::map<String, std::vector<String>> wordAssociations;


	String GetRandomFunFact();
	String HandleGameInput(String userInput);
	String HandleTypingTestInput(String userInput);
	String GetRandomTypingTest();
	String typingTestModeFeedback(int speed);
	String GetMotivationalQuote();
	String GetUserFeedback();

public:
    __fastcall TForm2(TComponent* Owner);
	String GetAIResponse(String userInput);
};

extern PACKAGE TForm2 *Form2;

#endif

