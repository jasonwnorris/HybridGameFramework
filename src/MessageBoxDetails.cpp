// MessageBoxDetails.hpp

// HGF Includes
#include <HGF/MessageBoxDetails.hpp>

namespace HGF
{
  const MessageBoxDetails MessageBoxDetails::DefaultDetails;

  MessageBoxDetails::MessageBoxDetails()
  {
    Level = MessageBoxLevel::Information;
    ButtonSet = MessageBoxButtonSet::OKSet;
  }
}
