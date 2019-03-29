function RTW_rtwnameSIDMap() {
	this.rtwnameHashMap = new Array();
	this.sidHashMap = new Array();
	this.rtwnameHashMap["<Root>"] = {sid: "ServoControl"};
	this.sidHashMap["ServoControl"] = {rtwname: "<Root>"};
	this.rtwnameHashMap["<Root>/Constant"] = {sid: "ServoControl:4"};
	this.sidHashMap["ServoControl:4"] = {rtwname: "<Root>/Constant"};
	this.rtwnameHashMap["<Root>/Data Type Conversion"] = {sid: "ServoControl:11"};
	this.sidHashMap["ServoControl:11"] = {rtwname: "<Root>/Data Type Conversion"};
	this.rtwnameHashMap["<Root>/Display"] = {sid: "ServoControl:9"};
	this.sidHashMap["ServoControl:9"] = {rtwname: "<Root>/Display"};
	this.rtwnameHashMap["<Root>/Display1"] = {sid: "ServoControl:10"};
	this.sidHashMap["ServoControl:10"] = {rtwname: "<Root>/Display1"};
	this.rtwnameHashMap["<Root>/Knob"] = {sid: "ServoControl:3"};
	this.sidHashMap["ServoControl:3"] = {rtwname: "<Root>/Knob"};
	this.rtwnameHashMap["<Root>/Scope"] = {sid: "ServoControl:7"};
	this.sidHashMap["ServoControl:7"] = {rtwname: "<Root>/Scope"};
	this.rtwnameHashMap["<Root>/Scope1"] = {sid: "ServoControl:8"};
	this.sidHashMap["ServoControl:8"] = {rtwname: "<Root>/Scope1"};
	this.rtwnameHashMap["<Root>/Serial Read"] = {sid: "ServoControl:2"};
	this.sidHashMap["ServoControl:2"] = {rtwname: "<Root>/Serial Read"};
	this.rtwnameHashMap["<Root>/Serial Write"] = {sid: "ServoControl:1"};
	this.sidHashMap["ServoControl:1"] = {rtwname: "<Root>/Serial Write"};
	this.getSID = function(rtwname) { return this.rtwnameHashMap[rtwname];}
	this.getRtwname = function(sid) { return this.sidHashMap[sid];}
}
RTW_rtwnameSIDMap.instance = new RTW_rtwnameSIDMap();
