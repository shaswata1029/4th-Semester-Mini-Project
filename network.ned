simple VehicleNode
	{
	    parameters:
	        int node_number;
	        int node_key;
	        @display("i=block/routing");
	    gates:
//	        input in;
	        output out1;
	}
	
simple MaliciousNode
{
    parameters:
            int node_number;
            int node_key;
	        @display("i=block/routing");
	    gates:
//	        input in;
	        output out1;
}	

simple TrafficLightNode
{
    parameters:
	        @display("i=block/routing");
	        int node1;
	        int node2;
	        int node3;
	        int node4;
	        int node5;
	        int secret;
	    gates:
	        input in1;
	        input in2;
	        input in3;
	        input in4;
	        input in5;
	        input in6;
	        input in7;
	        input in8;
	        output out;
	        
}

simple FinalNode{
    parameters:
	        @display("i=block/routing");
	    gates:
	        input in;
}


	
	
	network Project
	{
	    submodules:
	        Node1: VehicleNode {
	            parameters:
	                node_number=1;
	                node_key=1053;
	                @display("i=,cyan");
	        }
	         Node2: VehicleNode {
	            parameters:
	                node_number=2;
	                node_key=2559;
	                @display("i=,cyan");
	        }
	         Node3: VehicleNode {
	            parameters:
	                node_number=3;
	                node_key=4711;
	                @display("i=,cyan");
	        }
	         Node4: VehicleNode {
	            parameters:
	                node_number=4;
	                node_key=7509;
	                @display("i=,cyan");
	        }
	         Node5: VehicleNode {
	            parameters:
	                node_number=5;
	                node_key=10953;
	                @display("i=,cyan");
	        }
	        Node6: MaliciousNode {
	            parameters:
	                node_number=2;
	                node_key=1054;
	                @display("i=,gold");
	        }
	         Node7: MaliciousNode {
	            parameters:
	                node_number=4;
	                node_key=1098;
	                @display("i=,gold");
	        }
	         Node8: MaliciousNode {
	            parameters:
	                node_number=5;
	                node_key=7500;
	                @display("i=,gold");
	        }
	        Node9: TrafficLightNode{
	            parameters:
	                @display("i=,blue");
	                node1=1053;
	                node2=2559;
	                node3=4711;
	                node4=7509;
	                node5=10953;
	                secret=193;
	        }
	         Node10: FinalNode{
	            parameters:
	                @display("i=,red");
	        }
	        
	    connections:
	        Node1.out1 --> {  delay = 200ms; } --> Node9.in1;
	        Node2.out1 --> {  delay = 200ms; } --> Node9.in2;
	        Node3.out1 --> {  delay = 200ms; } --> Node9.in3;
	        Node4.out1 --> {  delay = 200ms; } --> Node9.in4;
	        Node5.out1 --> {  delay = 200ms; } --> Node9.in5;
	        Node6.out1 --> {  delay = 200ms; } --> Node9.in6;
	        Node7.out1 --> {  delay = 200ms; } --> Node9.in7;
	        Node8.out1 --> {  delay = 200ms; } --> Node9.in8;
	        Node9.out  --> {  delay = 300ms; } --> Node10.in;
	}