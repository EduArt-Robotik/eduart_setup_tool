#include "eduart_software_service.hpp"
#include "eduart_software.hpp"

namespace eduart {
namespace setup_tool {

static bool is_installed(const EduArtSoftware& software)
{
  
}

EduArtSoftwareService::EduArtSoftwareService(const EduArtSoftware& software)
  : _software(software)
{

}

EduArtSoftwareService::~EduArtSoftwareService()
{

}

} // end namespace setup tool
} // end namespace eduart
