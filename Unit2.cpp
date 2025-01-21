#include <fmx.h>
#pragma hdrstop

#include "Unit2.h"
#include <vector>
#include <string>
#include <map>
#include <cstdlib>
#include <ctime>

#pragma package(smart_init)
#pragma resource "*.fmx"
#pragma resource ("*.Windows.fmx", _PLAT_MSWINDOWS)
#pragma resource ("*.Surface.fmx", _PLAT_MSWINDOWS)

TForm2 *Form2;


__fastcall TForm2::TForm2(TComponent* Owner)
	: TForm(Owner)
{
	isGameActive = false;
	currentGameMode = "";
}


String TForm2::GetRandomFunFact()
{
    std::vector<String> funFacts = {
        "The average university student will write around 100,000 words in a year.",
        "Research shows that coffee can improve memory and cognitive performance — perfect for exam time!",
        "The longest university lecture in history lasted 35 hours straight.",
        "In 2019, over 200 million students were enrolled in universities worldwide.",
        "One of the most common stress factors for students is 'decision fatigue' from making countless small choices every day.",
        "The term 'student' comes from the Latin word 'studere,' meaning 'to be diligent.'",
        "You are more likely to forget a 30-minute lecture if you don't take notes during it.",
        "University students in Finland have the lowest dropout rate compared to the rest of the world.",
        "Over 50% of university students report using a planner to stay organized with assignments and exams.",
        "In the UK, 1 in 5 students take out a loan for their studies.",
        "Students who get 7 to 9 hours of sleep perform better academically than those who don't get enough rest.",
        "The average student spends 10-15 hours per week on homework outside of class.",
        "University students are more likely to skip meals due to studying or busy schedules.",
        "In some countries, universities host 'all-nighters' where students study through the night with free coffee and snacks.",
        "There are universities where students can take naps in designated nap areas to help with focus and productivity.",
        "The first student loans were introduced in the 1940s to allow more people access to higher education.",
        "Group study sessions can help students retain information better than studying alone.",
        "In 2015, a study revealed that 40% of students on college campuses feel 'extremely stressed.'",
        "Some universities offer pet therapy programs to help students cope with stress during finals week.",
        "The first university in the world, the University of al-Qarawiyyin, was founded in 859 in Morocco."
    };

    if (funFacts.empty()) {
        return "No fun facts available!";
    }

    int randomIndex = std::rand() % funFacts.size();
    return funFacts[randomIndex];
}




String TForm2::typingTestModeFeedback(int speed)
{
    if (speed > 60) {
        return "Excellent! Your typing speed is impressive.";
    } else if (speed >= 40) {
        return "Good! Keep practicing to improve further.";
    } else {
        return "Needs improvement. Keep practicing!";
    }
}


String TForm2::GetRandomTypingTest()
{
	int randomIndex = std::rand() % typingSentences.size();
	currentSentenceLength = typingSentences[randomIndex].Length();
	return typingSentences[randomIndex];
}


String TForm2::HandleTypingTestInput(String userInput)
{
	TDateTime endTime = Now();
	double timeTaken = (endTime - startTime).Val * 86400;

	int wordsPerMinute = static_cast<int>((currentSentenceLength / 5.0) / (timeTaken / 60));

	String feedback = typingTestModeFeedback(wordsPerMinute);
	isGameActive = false;
	currentGameMode = "";

	return "Typing Speed: " + IntToStr(wordsPerMinute) + " WPM. " + feedback;
}


String TForm2::HandleGameInput(String userInput)
{
    if (currentGameMode == "typing_test") {
        return HandleTypingTestInput(userInput);
    } else if (currentGameMode == "word_association") {
        if (userInput == "stop") {
            isGameActive = false;
            currentGameMode = "";
            return "Game stopped. Thank you for playing!";
        } else {
            if (wordAssociations.find(userInput) != wordAssociations.end()) {
                std::vector<String> possibleWords = wordAssociations[userInput];
                int randomIndex = std::rand() % possibleWords.size();
                String aiWord = possibleWords[randomIndex];
                return "AI: " + aiWord + " | You: " + userInput + ". Let's continue!";
            } else {
                return "AI: I don't have an association for that word. Please try another!";
            }
        }
    }
    return "";
}


String TForm2::GetAIResponse(String userInput)
{
    userInput = userInput.LowerCase();

    if (isGameActive) {
        return HandleGameInput(userInput);
    }

    if (knowledgeBase.find(userInput) != knowledgeBase.end()) {
        return knowledgeBase[userInput];
    }

    if (userInput.Pos("hello") > 0 || userInput.Pos("hi") > 0) {
        return "Hello there! How can I help you today?";
    } else if (userInput.Pos("bye") > 0) {
        return "Goodbye! Have a great day!";
    } else if (userInput.Pos("i want to play a game") > 0) {
        return "Sure! Choose a game:\n1. Word Association\n2. Typing Speed Test";
    } else if (userInput == "1") {
        isGameActive = true;
        currentGameMode = "word_association";
        return "Starting Word Association game. Type 'stop' to end.";
    } else if (userInput == "2") {
        isGameActive = true;
        currentGameMode = "typing_test";
        String sentence = GetRandomTypingTest();
		startTime = Now();
		return "Type this sentence: \"" + sentence + "\"";
    }

    ShowMessage("I don't know the answer to that. Can you teach me?");
    String userAnswer = InputBox("Teach AI", "Please provide the answer:", "");
    if (!userAnswer.IsEmpty()) {
        knowledgeBase[userInput] = userAnswer;
        return "Thank you for teaching me! I'll remember that.";
    }

    return "Sorry, I couldn't understand. Can you rephrase?";
}


String TForm2::GetMotivationalQuote()
{
    std::vector<String> quotes = {
        "Believe you can and you're halfway there.",
        "The only way to do great work is to love what you do.",
        "Success is not the key to happiness. Happiness is the key to success.",
        "Don’t watch the clock; do what it does. Keep going.",
        "It always seems impossible until it's done.",
        "Surround yourself with only people who are going to lift you higher.",
        "University is not just a place to get a degree, it's a place to grow and discover who you are.",
        "The best way to predict your future is to create it.",
        "Success is the sum of small efforts, repeated day in and day out.",
        "Friends are the family you choose.",
        "Education is the most powerful weapon you can use to change the world.",
        "The more that you read, the more things you will know. The more that you learn, the more places you’ll go.",
        "Don’t wait for the perfect moment, take the moment and make it perfect.",
        "True friends stab you in the front.",
        "A good friend knows all your best stories, but a best friend has lived them with you.",
        "You don't have to be great to start, but you have to start to be great.",
        "Success is not final, failure is not fatal: It is the courage to continue that counts.",
        "Your education is a dress rehearsal for a life that is yours to lead.",
        "The only limit to our realization of tomorrow is our doubts of today.",
        "Friendship is born at that moment when one person says to another, 'What! You too? I thought I was the only one.'",
        "Success usually comes to those who are too busy to be looking for it.",
        "In the middle of difficulty lies opportunity.",
        "The road to success is dotted with many tempting parking spaces.",
        "The best way to learn is to do. Success is built upon the courage to try.",
        "Your vibe attracts your tribe."
    };

    return quotes[std::rand() % quotes.size()];
}



String TForm2::GetUserFeedback()
{
    return InputBox("Feedback", "Please provide your feedback:", "");
}


void __fastcall TForm2::ClosebtnClick(TObject *Sender)
{
	String feedback = GetUserFeedback();
	String quote = GetMotivationalQuote();

	ShowMessage("Thank you for your feedback!\nRemember: " + quote);
	Application->Terminate();
}


void __fastcall TForm2::btnSendClick(TObject *Sender)
{
    String userInput = edtUserInput->Text;

    if (userInput.Length() > 0) {
        lblGreeting->Visible = false;
        Convo->Lines->Add("You: " + userInput);

        String aiResponse = GetAIResponse(userInput);
        Convo->Lines->Add("AI: " + aiResponse);

        edtUserInput->Text = "";
		Convo->GoToTextEnd();
	} else {
        ShowMessage("Please enter a message!");
    }
}


void __fastcall TForm2::FormCreate(TObject *Sender)
{
	std::srand(std::time(0));
    lblFunFact->Text = GetRandomFunFact();
    Convo->Lines->Clear();


    typingSentences = {
        "The quick brown fox jumps over the lazy dog.",
        "Practice makes a man perfect.",
        "Coding is fun and challenging.",
        "Every moment is a fresh beginning.",
        "Success is not final, failure is not fatal."
    };


    wordAssociations = {
    {"apple", {"banana", "orange", "pear", "grape", "cherry", "peach", "kiwi", "plum", "mango", "melon"}},
    {"dog", {"cat", "rabbit", "hamster", "bird", "fish", "puppy", "kitten", "turtle", "lizard", "horse"}},
    {"car", {"truck", "motorcycle", "bicycle", "van", "bus", "scooter", "train", "airplane", "boat", "taxi"}},
	{"sun", {"moon", "star", "planet", "sky", "cloud", "rain", "wind", "solar", "eclipse", "sunset"}},
    {"book", {"pen", "paper", "notebook", "journal", "library", "reading", "author", "publisher", "story", "page"}},
    {"computer", {"keyboard", "mouse", "monitor", "software", "hardware", "internet", "programming", "coding", "website", "laptop"}},
    {"coffee", {"tea", "milk", "sugar", "latte", "espresso", "cappuccino", "mocha", "iced", "brew", "bean"}},
    {"school", {"university", "college", "teacher", "student", "classroom", "library", "homework", "study", "assignment", "exam"}},
    {"music", {"song", "melody", "guitar", "piano", "drums", "concert", "artist", "album", "lyrics", "band"}},
    {"food", {"pizza", "burger", "sushi", "pasta", "salad", "ice cream", "chocolate", "fruit", "vegetable", "sandwich"}},
    {"nature", {"tree", "flower", "grass", "river", "mountain", "ocean", "lake", "forest", "wildlife", "sky"}},
    {"art", {"painting", "sculpture", "drawing", "gallery", "artist", "canvas", "color", "abstract", "museum", "portrait"}},
    {"travel", {"vacation", "plane", "hotel", "destination", "tourism", "trip", "journey", "sightseeing", "beach", "mountain"}},
    {"fashion", {"clothing", "shoes", "accessories", "style", "designer", "runway", "outfit", "trendy", "color", "fabric"}},
    {"exercise", {"gym", "running", "swimming", "yoga", "workout", "fitness", "strength", "endurance", "health", "stretching"}},
    {"technology", {"innovation", "AI", "robotics", "smartphone", "tablet", "internet", "cloud", "app", "website", "gadget"}},
    {"movies", {"action", "comedy", "drama", "romance", "thriller", "director", "actor", "cinema", "screenplay", "plot"}},
    {"holiday", {"Christmas", "Easter", "Halloween", "New Year's", "Thanksgiving", "birthday", "vacation", "celebration", "party", "gifts"}},
    {"science", {"physics", "biology", "chemistry", "astronomy", "experiment", "research", "laboratory", "theory", "cell", "atom"}},
    {"sports", {"football", "basketball", "cricket", "tennis", "baseball", "soccer", "athletics", "swimming", "boxing", "gymnastics"}},
    {"fitness", {"health", "strength", "cardio", "endurance", "yoga", "stretching", "weightlifting", "wellness", "exercise", "workout"}},
    {"weather", {"sunny", "rainy", "windy", "snowy", "stormy", "cloudy", "temperature", "forecast", "humidity", "weather"}},
    {"animal", {"cat", "dog", "elephant", "tiger", "lion", "giraffe", "zebra", "koala", "kangaroo", "panda"}},
    {"phone", {"smartphone", "charger", "battery", "screen", "call", "message", "app", "contacts", "ringtone", "camera"}},
    {"computer", {"mouse", "keyboard", "monitor", "internet", "software", "hardware", "laptop", "programming", "code", "server"}},
    {"book", {"novel", "fiction", "literature", "author", "publisher", "library", "e-book", "bookmark", "chapter", "cover"}},
    {"vacation", {"holiday", "beach", "resort", "trip", "tourism", "destination", "plane", "hotel", "sightseeing", "travel"}},
    {"family", {"mother", "father", "sister", "brother", "grandparent", "aunt", "uncle", "cousin", "parent", "home"}},
    {"school", {"teacher", "student", "class", "homework", "study", "exam", "library", "university", "test", "course"}},
    {"fashion", {"style", "outfit", "clothes", "trend", "accessories", "design", "runway", "shoes", "jewelry", "makeup"}},
    {"city", {"town", "suburb", "village", "district", "street", "neighborhood", "downtown", "countryside", "urban", "metropolis"}},
    {"car", {"engine", "wheel", "steering", "tire", "window", "door", "mirror", "accelerator", "brake", "gear"}},
    {"exercise", {"gym", "cardio", "weightlifting", "stretching", "strength", "endurance", "fitness", "workout", "yoga", "pilates"}},
    {"art", {"drawing", "painting", "sculpture", "design", "artist", "gallery", "abstract", "portrait", "landscape", "canvas"}},
    {"party", {"friends", "celebration", "music", "dance", "drinks", "food", "fun", "gathering", "birthday", "event"}},
    {"beach", {"sand", "ocean", "sun", "waves", "swim", "surf", "sea", "umbrella", "towel", "beachball"}},
    {"gym", {"exercise", "weights", "cardio", "workout", "fitness", "strength", "yoga", "endurance", "stretching", "health"}},
    {"study", {"notes", "books", "lecture", "test", "exam", "homework", "research", "studygroup", "review", "sleep"}},
    {"food", {"pizza", "burger", "pasta", "sushi", "icecream", "salad", "fruits", "vegetables", "cheese", "bread"}},
    {"language", {"English", "French", "Spanish", "German", "Chinese", "Japanese", "Arabic", "Russian", "Italian", "Portuguese"}},
    {"game", {"play", "video", "board", "card", "fun", "challenge", "score", "level", "competition", "winning"}},
    {"shopping", {"clothes", "shoes", "sale", "discount", "store", "online", "market", "mall", "buy", "checkout"}},
    {"adventure", {"explore", "travel", "journey", "discovery", "exciting", "challenge", "experience", "outdoors", "camping", "mountain"}}
};

}


void __fastcall TForm2::funfactbuttonClick(TObject *Sender)
{
    String fact = GetRandomFunFact();
    lblFunFact->Text = fact;
}


void __fastcall TForm2::edtUserInputKeyDown(TObject *Sender, WORD &Key, TShiftState Shift)
{
	if (Key == VK_RETURN) {
        btnSendClick(Sender);
    }
}




