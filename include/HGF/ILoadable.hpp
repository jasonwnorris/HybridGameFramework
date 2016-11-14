// ILoadable.hpp

#ifndef __HGF_ILOADABLE_HPP__
#define __HGF_ILOADABLE_HPP__

// STL Includes
#include <string>

namespace HGF
{
  template<typename T> class ILoadable
  {
    public:
      ILoadable() = default;
      virtual ~ILoadable() = default;

      virtual bool Load(const std::string& p_Filename, const T& p_Options) = 0;
      virtual void Unload() = 0;

    protected:
      bool m_IsLoaded;
  };
}

#endif
