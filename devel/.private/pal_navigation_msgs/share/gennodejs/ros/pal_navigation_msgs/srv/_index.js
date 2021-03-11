
"use strict";

let GetNodes = require('./GetNodes.js')
let GetSubMap = require('./GetSubMap.js')
let ChangeBuilding = require('./ChangeBuilding.js')
let SetSubMapFloor = require('./SetSubMapFloor.js')
let SafetyZone = require('./SafetyZone.js')
let DisableEmergency = require('./DisableEmergency.js')
let FinalApproachPose = require('./FinalApproachPose.js')
let GetMapConfiguration = require('./GetMapConfiguration.js')
let SaveMap = require('./SaveMap.js')
let RenameMap = require('./RenameMap.js')
let ListMaps = require('./ListMaps.js')
let GetPOI = require('./GetPOI.js')
let SetMapConfiguration = require('./SetMapConfiguration.js')
let SetPOI = require('./SetPOI.js')
let Acknowledgment = require('./Acknowledgment.js')
let VisualLocRecognize = require('./VisualLocRecognize.js')

module.exports = {
  GetNodes: GetNodes,
  GetSubMap: GetSubMap,
  ChangeBuilding: ChangeBuilding,
  SetSubMapFloor: SetSubMapFloor,
  SafetyZone: SafetyZone,
  DisableEmergency: DisableEmergency,
  FinalApproachPose: FinalApproachPose,
  GetMapConfiguration: GetMapConfiguration,
  SaveMap: SaveMap,
  RenameMap: RenameMap,
  ListMaps: ListMaps,
  GetPOI: GetPOI,
  SetMapConfiguration: SetMapConfiguration,
  SetPOI: SetPOI,
  Acknowledgment: Acknowledgment,
  VisualLocRecognize: VisualLocRecognize,
};
