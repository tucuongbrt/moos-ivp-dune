#include "ImcBridge.h"

ImcBridge::ImcBridge() {
  // empty
}

ImcBridge::~ImcBridge() {
  // empty
}


bool ImcBridge::OnNewMail (MOOSMSG_LIST & Mail) {
  // process it
  MOOSMSG_LIST::iterator q;
  for(q=Mail.begin(); q!=Mail.end(); q++) {
    q->Trace();
  }
  return(true);
}
  
bool ImcBridge::OnConnectToServer () {
  return(Register("X", 0.0));
} 
  
bool ImcBridge::Iterate ( ) {
  std :: vector<unsigned char> X(100) ; 
  Notify("X" ,X) ;
  return true ;
}

Message * ImcBridge::imcPoll() {
  if (m_poll.poll(0)) {
    Address addr;
    uint16_t rv = sock_receive.read(bfr, 65535, &addr);
    IMC::Message * msg = IMC::Packet::deserialize(bfr, rv);
    return msg;
  }
  return NULL;
}

bool ImcBridge::imcSend(Message * msg, std::string addr, int port) {
  DUNE::Utils::ByteBuffer bb;
  try {
    IMC::Packet::serialize(msg, bb);
    return sock_send.write(bb.getBuffer(), msg->getSerializationSize(),
        Address(addr.c_str()), port);
  }
  catch (std::runtime_error& e)
  {
    std::cerr << "ERROR: " << ": " << e.what() << "\n";
    return false;
  }
  return true;
}
