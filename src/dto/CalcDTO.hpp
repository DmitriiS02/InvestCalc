#ifndef DTOs_hpp
#define DTOs_hpp

#include "oatpp/core/macro/codegen.hpp"
#include "oatpp/core/Types.hpp"

#include OATPP_CODEGEN_BEGIN(DTO)

/**
 *  Data Transfer Object. Object containing fields only.
 *  Used in API for serialization/deserialization and validation
 */
class CalcDtoResponse : public oatpp::DTO {
  DTO_INIT(CalcDtoResponse, DTO)

  DTO_FIELD(Vector<Int32>, years);
  DTO_FIELD(Int64, startSum);
  DTO_FIELD(Float32, percent);
};

class CalcDtoRequest : public oatpp::DTO {
  DTO_INIT(CalcDtoRequest, DTO)
  DTO_FIELD(Int64, startSum);
  DTO_FIELD(Float32, percent);
  DTO_FIELD(Int32, amount); // of years
};

class HelloDto : public oatpp::DTO {
  DTO_INIT(HelloDto, DTO)
  DTO_FIELD(Int32, statusCode);
  DTO_FIELD(String, message);

};


#include OATPP_CODEGEN_END(DTO)

#endif /* DTOs_hpp */
