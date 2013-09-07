#include "modeloperation.h"
#include "boost/format.hpp"

ModelOperation::ModelOperation(ModelOperationRanges::ModelOperationEnum operationVal,
                               std::string operationName,
                               std::string operationExplanation,
                               bool operatesOnIndex) :
    m_operationVal(operationVal),
    m_operationName(operationName),
    m_operationExplanation(operationExplanation),
    m_operatesOnIndex(operatesOnIndex)
{
}
