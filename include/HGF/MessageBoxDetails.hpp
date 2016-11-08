// MessageBoxDetails.hpp

#ifndef __HGF_MESSAGEBOXDETAILS_HPP__
#define __HGF_MESSAGEBOXDETAILS_HPP__

// HGF Includes
#include <HGF/MessageBoxButtonSet.hpp>
#include <HGF/MessageBoxLevel.hpp>
#include <HGF/MessageBoxScheme.hpp>

namespace HGF
{
  struct MessageBoxDetails
  {
    static const MessageBoxDetails DefaultDetails;

    MessageBoxLevel Level;
    MessageBoxButtonSet ButtonSet;
    MessageBoxScheme Scheme;

    MessageBoxDetails();
  };
}

#endif
