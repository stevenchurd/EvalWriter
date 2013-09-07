#ifndef MODELOPERATION_H
#define MODELOPERATION_H

#include <string>
#include <stdexcept>
#include <vector>

#ifndef Q_MOC_RUN
#include <boost/format.hpp>
#include "globalenums.h"
#endif

class ModelOperation
{
    public:
        ModelOperation(ModelOperationRanges::ModelOperationEnum operationVal,
                       std::string operationName,
                       std::string operationExplanation,
                       bool operatesOnIndex);

        template <typename InputIterator>
        std::string getOperationExplanation(InputIterator replaceStrsBegin,
                  InputIterator replaceStrsEnd) const;

        ModelOperationRanges::ModelOperationEnum getOperationEnum(void) const { return m_operationVal; }
        std::string getOperationsName(void) const { return m_operationName; }
        bool operatesOnIndex(void) const { return m_operatesOnIndex; }

    private:
        ModelOperationRanges::ModelOperationEnum m_operationVal;
        std::string m_operationName;
        std::string m_operationExplanation;
        bool m_operatesOnIndex;
};


template <typename InputIterator>
std::string ModelOperation::getOperationExplanation(InputIterator replaceStrsBegin,
                                                    InputIterator replaceStrsEnd) const
{
    boost::format fmter(m_operationExplanation);

    std::for_each(replaceStrsBegin, replaceStrsEnd,
                  [&fmter] (std::string replacementString)
    {
        fmter % replacementString;
    });

    return fmter.str();
}


#endif // MODELOPERATION_H
