#ifndef MyController_hpp
#define MyController_hpp

#include "dto/CalcDTO.hpp"
#include "oatpp/core/Types.hpp"
#include "oatpp/web/server/api/ApiController.hpp"
#include "oatpp/parser/json/mapping/ObjectMapper.hpp"
#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/macro/component.hpp"

#include OATPP_CODEGEN_BEGIN(ApiController) //<-- Begin Codegen


class CalcController : public oatpp::web::server::api::ApiController {
public:
  /**
   * Constructor with object mapper.
   * @param objectMapper - default object mapper used to serialize/deserialize DTOs.
   */
  explicit CalcController(OATPP_COMPONENT(std::shared_ptr<ObjectMapper>, objectMapper))
      : oatpp::web::server::api::ApiController(objectMapper)
  {}
public:

  ENDPOINT("POST", "/complex_percent", handler, BODY_DTO(Object< CalcDtoRequest >, calcDtoRequest)) {

    auto responseDto = CalcDtoResponse::createShared();
    responseDto->years = {};

    auto calculated = calculateComplexPercent(
        calcDtoRequest->startSum,
        calcDtoRequest->percent,
        calcDtoRequest->amount);
    for (auto const &item : calculated){
      responseDto->years->push_back(item);
    }

    responseDto->percent = calcDtoRequest->percent;
    responseDto->startSum = calcDtoRequest->startSum;
    return createDtoResponse(Status::CODE_200, responseDto);
  }
  ENDPOINT("GET", "/", root) {
    auto dto = HelloDto::createShared();
    dto->statusCode = 200;
    dto->message = "Hello, it works!";
    return createDtoResponse(Status::CODE_200, dto);
  }

private:
  static std::vector<long long> calculateComplexPercent(long long startSum, double percent, int amount) {
    auto sum = (double) startSum;
    std::vector<long long> years{};
    for (int i = 0; i <= amount; i++) {
      years.push_back((long long) sum);
      sum *= percent;
    }
    return years;
  }
};

#include OATPP_CODEGEN_END(ApiController) //<-- End Codegen

#endif /* MyController_hpp */
