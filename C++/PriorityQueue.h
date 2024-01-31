#pragma once


/**
*
* 
* 
*   This is a module I created to implement an exercise I remembered from OOP class, in which the professor proposed
* an exercise where we had a standard queue for an imaginary hospital system, where we had to create a program that got 
* every new person to be included in the queue, based on characteristics. So, the priority order was:
*   Pregnant Women -> elder women -> elder men -> children -> women -> men. It was pretty cool, it was done in Java, and I will re
* make it in C++ here.
* 
* 
* 
* 
*/

#include <string>
#include <exception>

namespace PriorityQueue {

	//Note: since I know what exactly kind of data will be coming, I'll not be using generic templates on this one


	enum AgeCategory {

		NEWBORN,
		CHILDREN,
		TEENAGER,
		YOUNG,
		ADULT,
		ELDER
	};




	class User {

	private:

		short int age;
		std::string name;
		bool gender; // 0 for man, 1 for women
		bool isPregnant;
		AgeCategory ageCategory;
		
	public:

		static int IsMan(bool value) { return (value == 0); }

		static int IsWomen(bool value) { return (value == 1); }

		User(short int age, std::string name, bool gender, bool pregnancy) {

			// Deal with age

			if (age < 0) throw std::exception("Invalid age!!!");

			this->age = age;

			// Set age category
			if (age <= 2) this->ageCategory = NEWBORN;
			else if (age > 2 || age <= 11)  this->ageCategory = CHILDREN;
			else if (age > 11 || age <= 17) this->ageCategory = TEENAGER;
			else if (age > 17 || age <= 25) this->ageCategory = YOUNG;
			else if (age > 25 || age <= 44) this->ageCategory = ADULT;
			else if (age > 44 || age <= 122) this->ageCategory = ELDER;
			else throw std::exception("Congratilations!! You broke guiness age world record!!!");

			this->name = name;

			this->gender = gender;

			if (IsMan(gender) || pregnancy) {
				throw std::exception("Oh boy...");
			}

			else if (IsWomen(gender) || pregnancy) {
				this->isPregnant = true;
			}

		}

		short int GetAge() { return this->age; }
		std::string GetName() { return this->name;}
		bool GetGender() { return this->gender; }
		AgeCategory GetCategory() { return this->ageCategory; }

	};


	class Queue {

	private:

		User* firstUser;
		User* lastUser;

		User* firstNewborn;
		User* lastNewborn;

		User* firstChildren;
		User* lastChildren;

		User* firstTeen;
		User* lastTeen;

		User* firstYoung;
		User* lastYoung;

		User* firstAdult;
		User* lastAdult;

		User* firstElder;
		User* lastElder;

		int queueSize;
		size_t MAX_SIZE;


	public:

		Queue(int maxSize) : MAX_SIZE(maxSize), queueSize(0) {

			firstUser = nullptr;
			lastUser = nullptr;

			firstNewborn = nullptr;
			lastNewborn = nullptr;

			firstChildren = nullptr;
			lastChildren = nullptr;

			firstTeen = nullptr;
			lastTeen = nullptr;

			firstYoung = nullptr;
			lastYoung = nullptr;

			firstAdult = nullptr;
			lastAdult = nullptr;

			firstElder = nullptr;
			lastElder = nullptr;

		}

		int GetSize() {
			return this->queueSize;
		}


		short int PeekAge(User user) {
			return 1;
		}










	};




}