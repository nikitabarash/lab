#pragma once

namespace blackjack {

	using namespace System;
	using namespace System::Windows::Forms;
	using namespace System::Drawing;

	public ref class game_form : public Form {
	private:
		int playerScore;    // Очки игрока
		int dealerScore;    // Очки дилера
		int playerBalance;  // Баланс игрока
		int currentBet;     // Текущая ставка

		Label^ labelPlayerScore;
		Label^ labelDealerScore;
		Label^ labelBalance;
		Label^ labelBet;

		Button^ buttonHit;
		Button^ buttonStand;
		Button^ buttonMakeBet;

	public:
		game_form(void) {
			InitializeComponent();
			InitializeGame();
		}

	protected:
		~game_form() {}

	private:
		void InitializeComponent() {
			this->Text = L"Blackjack Game";
			this->Size = System::Drawing::Size(800, 600);
			this->MaximizeBox = false;

			// Лейблы для очков и баланса
			labelPlayerScore = gcnew Label();
			labelDealerScore = gcnew Label();
			labelBalance = gcnew Label();
			labelBet = gcnew Label();

			// Кнопки управления
			buttonHit = gcnew Button();
			buttonStand = gcnew Button();
			buttonMakeBet = gcnew Button();

			// Настройка элементов
			SetupUI();
		}

		void SetupUI() {
			// Лейблы
			labelPlayerScore->Text = L"Player Score: 0";
			labelPlayerScore->Location = Point(50, 50);
			labelPlayerScore->Size = System::Drawing::Size(200, 30);

			labelDealerScore->Text = L"Dealer Score: 0";
			labelDealerScore->Location = Point(50, 100);
			labelDealerScore->Size = System::Drawing::Size(200, 30);

			labelBalance->Text = L"Balance: $1000";
			labelBalance->Location = Point(50, 150);
			labelBalance->Size = System::Drawing::Size(200, 30);

			labelBet->Text = L"Current Bet: $0";
			labelBet->Location = Point(50, 200);
			labelBet->Size = System::Drawing::Size(200, 30);

			// Кнопки
			buttonMakeBet->Text = L"Make Bet";
			buttonMakeBet->Location = Point(50, 300);
			buttonMakeBet->Size = System::Drawing::Size(100, 40);
			buttonMakeBet->Click += gcnew EventHandler(this, &game_form::OnMakeBetClick);

			buttonHit->Text = L"Hit";
			buttonHit->Location = Point(200, 300);
			buttonHit->Size = System::Drawing::Size(100, 40);
			buttonHit->Click += gcnew EventHandler(this, &game_form::OnHitClick);

			buttonStand->Text = L"Stand";
			buttonStand->Location = Point(350, 300);
			buttonStand->Size = System::Drawing::Size(100, 40);
			buttonStand->Click += gcnew EventHandler(this, &game_form::OnStandClick);

			// Добавление элементов на форму
			this->Controls->Add(labelPlayerScore);
			this->Controls->Add(labelDealerScore);
			this->Controls->Add(labelBalance);
			this->Controls->Add(labelBet);
			this->Controls->Add(buttonMakeBet);
			this->Controls->Add(buttonHit);
			this->Controls->Add(buttonStand);
		}

		void InitializeGame() {
			playerBalance = 1000; // Начальный баланс
			currentBet = 0;
			playerScore = 0;
			dealerScore = 0;
		}

		// События для кнопок
		void OnMakeBetClick(Object^ sender, EventArgs^ e) {
			// Устанавливаем ставку (по умолчанию 100)
			currentBet = 100;
			playerBalance -= currentBet;
			labelBalance->Text = L"Balance: $" + playerBalance;
			labelBet->Text = L"Current Bet: $" + currentBet;
		}

		void OnHitClick(Object^ sender, EventArgs^ e) {
			// Раздаем карту игроку и обновляем очки
			Random^ random = gcnew Random();
			int cardValue = random->Next(1, 11); // Карта от 1 до 10
			playerScore += cardValue;
			labelPlayerScore->Text = L"Player Score: " + playerScore;

			// Проверяем, не перебрал ли игрок
			if (playerScore > 21) {
				MessageBox::Show(L"You lose!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
				ResetGame();
			}
		}

		void OnStandClick(Object^ sender, EventArgs^ e) {
			// Ход дилера
			Random^ random = gcnew Random();
			while (dealerScore < 17) {
				int cardValue = random->Next(1, 11);
				dealerScore += cardValue;
			}
			labelDealerScore->Text = L"Dealer Score: " + dealerScore;

			// Определяем победителя
			if (dealerScore > 21 || playerScore > dealerScore) {
				playerBalance += currentBet * 2;
				MessageBox::Show(L"You win!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}
			else {
				MessageBox::Show(L"You lose!", L"Game Over", MessageBoxButtons::OK, MessageBoxIcon::Information);
			}

			ResetGame();
		}

		void ResetGame() {
			playerScore = 0;
			dealerScore = 0;
			currentBet = 0;

			labelPlayerScore->Text = L"Player Score: 0";
			labelDealerScore->Text = L"Dealer Score: 0";
			labelBet->Text = L"Current Bet: $0";
			labelBalance->Text = L"Balance: $" + playerBalance;
		}
	};
}