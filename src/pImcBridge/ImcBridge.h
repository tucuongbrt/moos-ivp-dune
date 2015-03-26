// MOOS-IMC bridge.
//
// March 26th, 2015

#include "MOOS/libMOOS/App/MOOSApp.h"
#include <DUNE/DUNE.hpp>
#include <DUNE/Network.hpp>
#include <DUNE/Network/Fragments.hpp>
using DUNE_NAMESPACES;

class ImcBridge : public CMOOSApp {
public:
  bool OnNewMail (MOOSMSG_LIST & Mail); 
  bool OnConnectToServer ();
  bool Iterate ( );
  Message * imcPoll();
  bool imcSend(Message * msg, std::string addr, int port);
  ~ImcBridge();
  ImcBridge();
private:
  UDPSocket sock_send, sock_receive;
  DUNE::IO::Poll m_poll;
  uint8_t* bfr;
};
