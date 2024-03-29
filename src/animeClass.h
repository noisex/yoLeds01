#ifndef __WAVE_CLASS_H
#define __WAVE_CLASS_H

#include <FastLED.h>
#include <unordered_set>
#include <vector>
#include "config.h"
#include "leds.h"

class animeClass
{
	public:	
		int indAnime	= 0;
		int indSetter 	= 0;	
		bool changed 	= false;   				// something chaged from web or irda
		uint8_t countWaves 		= 0;
		uint8_t countRanges 	= 0;
		uint8_t currentNoWaves 	= 0;			// индекс текущей активности, надо для переключалки их по кругу через "чэнджер" с ИРы в nextWave()
		
		std::vector <uint8_t> vButton;				// vector, храним список активностей, отсортированных по списку вывода на сайте
		std::vector <uint8_t> vRanges;				// vector, храним список рэнджой, отсортированных по списку вывода на сайте
		std::unordered_set <uint8_t> forSave;		// сет для НЕ СОХРАНЕННЫХ ключей "ИД волн", которые необходимо сохранить, так как у них что-то изменилось
    	std::unordered_set <uint8_t> keysAll;  		// сет для ВСЕХ ИД, чекаем уникальность введенных ИД для активностей, вроде как пофик, но вот чёта хочется.
    	std::unordered_set <uint8_t> keyRange;  	// сет для РЭНДЖЕЙ - полоски-двиалки для сайта
    	std::unordered_set <uint8_t> keyButton; 	// сет для КНОПОК - активности типа статик или анимашка для веба, по факту - хранит активные активности.
		std::pair<std::unordered_set <uint8_t> :: iterator, bool> itKeys; // итератор для анордеред_мапы с ИД активностей

		/*		Какая-то функция, которая запускается после всего для чего-то, что надо сделать потом.*/
		void makeWebLists();
		void applyWaveData( const waveItem &c);
		void changeWave( uint8_t id, int webValue);		

		/*Возвращает true ( bool Ledas.changed), 
		если в настройках с сайта или ИРы что-то поменялось.
		Сбрасывается на false, после первого обращения к себе.*/
		bool isChanged(){
			bool result = this->changed;
			this->changed = false;
			return result;
		}

		/*
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptStatic указатель на функию аминации, выполняется разово ( не в лупе) = &staticFuuctionName
		@param forWeb публиковать на сайте ( будет в виде кнопки вызова анимации), позиция в странице зависит от порядка при добавлении
		@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)*/
		void addStatic( 	uint8_t id, const String& name, void (*ptStatic)(), 	bool forWeb = false, 	uint8_t polDefault 	= 9);		
		/*
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptAnime указатель на функию аминации, выполняется в цикле loop = &staticFuuctionName
		@param forWeb публиковать на сайте ( будет в виде кнопки вызова анимации), позиция в странице зависит от порядка при добавлении
		@param polDefault ИД политры по-умолчанию для анимации, берется из таблицы myPal из palettes.cpp ( 9 - радуга)
		@param ptAnimePre указатель на функция "пре", выполнится один раз перед первым запуском функции с анимацией = &staticFuuctionName*/
		void addAmine( 		uint8_t id, const String& name, void (*ptAnime)(), 		bool forWeb = false, 	uint8_t polDefault 	= 9, 	void (*ptAnimePre)() = nullptr);
		/*
		Добавляем "сеттер", добавляется на страницу в виде рэнджа, вызывается из веба, при изменениии рэнджа с передацей значения в функцию.
		@param id Unical ID. irDA code даже лучше будет
		@param name Animation name for web ( Here - Nah)
		@param ptSetter указатель на функцию "сеттер" = &staticFuuctionName
		@param min мин
		@param max  макс*/
		void addSetter( 	uint8_t id, const String& name, void (*ptSetter)(int), 	int min = 0, int max = 255, bool forWeb = true );
		/*
		Добавляем "Чэнджер", для тыканья с пульта ИД и вызова функций
			с передачей +/-дельты в нее. Не для веба.

		@param id Unical ID. irDA code даже лучше будет. Доп коды в таблице keyCodes в irda.cpp
		@param name Animation name ( Here - Nah), просто для понимания, что это такое.
		@param ptChanger pointer to changer function = &staticFuuctionName
		@param delta +/- add/sub, передаем это значение в функцию*/
		void addChanger( 	uint8_t id, const String& name, void (*ptChanger)(int),	signed char delta = 1);		

		/* Обработка ИР приемника, через обход мапы mButtons
		и сохранение в ЕЕПроМ, если код с передатчика нашелся.
		Принимает входные параметры с вебсерра
		@param codeFromWeb свой ИК-код, приходит от веб-кдента
		@param webValue значение для установки параметров, приходит от веб-клиента*/
		void animeSet( uint8_t id = 0, int webValue = 0);

		bool insertID( uint8_t id);
		bool isID( 	uint8_t id);

		static void nextWave( int delta = 1);
	
	private:
		waveItem* addDefault( uint8_t id);
};

// в тут хранятся... да тут только одбавляшки и сэты из индексов уже добавленных активностей. еще isChanged есть полезный.
extern animeClass a;

#endif