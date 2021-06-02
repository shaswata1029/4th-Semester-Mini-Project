
#include<bits/stdc++.h>
#include <omnetpp.h>
#include "message_m.h"

    using namespace omnetpp;

     class VehicleNode : public cSimpleModule
    {
      protected:
        virtual void initialize() override;
    };

    Define_Module(VehicleNode);


    class MaliciousNode : public cSimpleModule
        {
          protected:
            virtual void initialize() override;
        };

        Define_Module(MaliciousNode);



    class TrafficLightNode : public cSimpleModule
               {
            private:
            int secret;
            std::vector<std::pair<int,int>>keys;
            protected:
           virtual void initialize() override;
           virtual void handleMessage(cMessage *msg) override;
           virtual bool decryptMessage(Message *msg);
               };

        Define_Module(TrafficLightNode);

    class FinalNode : public cSimpleModule
         {
            private:
            int counter;
            public:
            FinalNode();
              virtual ~FinalNode();
           protected:
           virtual void handleMessage(cMessage *msg) override;
         };

       Define_Module(FinalNode);


       struct fraction {
           int num, den;

           // A fraction consists of a
           // numerator and a denominator
           fraction(int n, int d)
           {
               num = n, den = d;
           }

           // If the fraction is not
           // in its reduced form
           // reduce it by dividing
           // them with their GCD
           void reduce_fraction(fraction& f)
           {
               int gcd = std::__gcd(f.num, f.den);
               f.num /= gcd, f.den /= gcd;
           }

           // Performing multiplication on the
           // fraction
           fraction operator*(fraction f)
           {
               fraction temp(num * f.num, den * f.den);
               reduce_fraction(temp);
               return temp;
           }

           // Performing addition on the
           // fraction
           fraction operator+(fraction f)
           {
               fraction temp(num * f.den + den * f.num,
                           den * f.den);

               reduce_fraction(temp);
               return temp;
           }
       };


       void TrafficLightNode::initialize(){
           keys.push_back({0,0});
           keys.push_back({1,par("node1")});
           keys.push_back({2,par("node2")});
           keys.push_back({3,par("node3")});
           keys.push_back({4,par("node4")});
           keys.push_back({5,par("node5")});
           secret=par("secret");
       }

       FinalNode::FinalNode()
                {
                   counter=0;
                }

       FinalNode::~FinalNode()
                {
                   counter=0;
                }

       void VehicleNode::initialize()
          {
            if (strcmp("Node1", getName()) == 0) {
                Message *msg = new Message();
                msg->setNodeKey(par("node_key"));
                msg->setNodeNumber(par("node_number"));
                msg->setOriginalMessage("Hello");
                send(msg, "out1");
                   }
            if (strcmp("Node3", getName()) == 0) {
                Message *msg = new Message();
                msg->setNodeKey(par("node_key"));
                msg->setNodeNumber(par("node_number"));
                msg->setOriginalMessage("Hello");
                send(msg, "out1");
                     }
            if (strcmp("Node5", getName()) == 0) {
                Message *msg = new Message();
                msg->setNodeKey(par("node_key"));
                msg->setNodeNumber(par("node_number"));
                msg->setOriginalMessage("Hello");
                send(msg, "out1");
                         }
         }

       void MaliciousNode::initialize()
       {
           if (strcmp("Node7", getName()) == 0) {
                         Message *msg = new Message();
                         msg->setNodeKey(par("node_key"));
                         msg->setNodeNumber(par("node_number"));
                         msg->setOriginalMessage("Hello");
                         send(msg, "out1");
                           }
       }


      void TrafficLightNode::handleMessage(cMessage *msg)
       {
          Message *tmsg = check_and_cast<Message *>(msg);
          bool isValid=decryptMessage(tmsg);
          if(isValid){
              EV<<"Given node is a valid node";
              bubble("Node is valid!! Forwarding Message");
              send(msg, "out");// send out the message
          }
          else{
              EV<<"Given node is a malicious node";
              bubble("Malicious node detected!! Message blocked");
              delete msg;
          }
       }

      bool TrafficLightNode::decryptMessage(Message *msg){

          std::vector<std::pair<int,int>>decryption_keys;
          decryption_keys.push_back({msg->getNodeNumber(),msg->getNodeKey()});
          if(msg->getNodeNumber()==1){
              decryption_keys.push_back({keys[msg->getNodeNumber()+1].first,keys[msg->getNodeNumber()+1].second});
              decryption_keys.push_back({keys[msg->getNodeNumber()+2].first,keys[msg->getNodeNumber()+2].second});
          }
          else if(msg->getNodeNumber()==keys.size()-1){
                decryption_keys.push_back({keys[msg->getNodeNumber()-1].first,keys[msg->getNodeNumber()-1].second});
                decryption_keys.push_back({keys[msg->getNodeNumber()-2].first,keys[msg->getNodeNumber()-2].second});
           }
          else{
              decryption_keys.push_back({keys[msg->getNodeNumber()-1].first,keys[msg->getNodeNumber()-1].second});
              decryption_keys.push_back({keys[msg->getNodeNumber()+1].first,keys[msg->getNodeNumber()+1].second});
          }


          fraction ans(0, 1);

              // Loop to iterate through the given
              // points
              for (int i = 0; i < 3; ++i) {

                  // Initializing the fraction
                  fraction l(decryption_keys[i].second, 1);
                  for (int j = 0; j < 3; ++j) {

                      // Computing the lagrange terms
                      if (i != j) {
                          fraction temp(-decryption_keys[j].first, decryption_keys[i].first - decryption_keys[j].first);
                          l = l * temp;
                      }
                  }
                  ans = ans + l;
              }

              // Return the secret
              EV<<endl<<"Generated key : "<<ans.num<<endl;
              if(ans.num==secret)
                  return true;

          return false;
      }

      void FinalNode::handleMessage(cMessage *msg)
             {
                bubble("message received");
                counter++;
                EV<<counter;
                delete msg;
             }




