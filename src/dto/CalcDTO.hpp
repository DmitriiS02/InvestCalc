/**
  * \file Файл с описанием структур запросов и ответов для бэкенда
 */

#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
  * \brief Класс структуры Запроса к бэкенду
  * \param startSum Стартовая сумма инвестиций
  * \param percent Годовой процент увеличения вложений
  * \param amount Число лет для инвестирования
*/
class CalcDtoRequest : public oatpp::DTO {
  DTO_INIT(CalcDtoRequest, DTO)
  DTO_FIELD(Int64, startSum);
  DTO_FIELD(Float32, percent);
  DTO_FIELD(Int32, amount); // of years
};

/**
  * \brief Класс структуры Ответа с результатом расчета
  * \param years Массив со значениями капитала по годам
  * \param startSum Стартовая сумма инвестиций (копируется из входного запроса)
  * \param percent Годовой процент увеличения вложений (копируется из входного запроса)
 */
class CalcDtoResponse : public oatpp::DTO {
  DTO_INIT(CalcDtoResponse, DTO)

  DTO_FIELD(Vector<Int32>, years);
  DTO_FIELD(Int64, startSum);
  DTO_FIELD(Float32, percent);
};

/**
  * \brief Класс структуры Ответа бэкенда на тестовый (ping) запрос
  * \param statusCode Статус ответа
  * \param message Сообщение от сервера
*/
class HelloDto : public oatpp::DTO {
  DTO_INIT(HelloDto, DTO)

  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);
};


#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
