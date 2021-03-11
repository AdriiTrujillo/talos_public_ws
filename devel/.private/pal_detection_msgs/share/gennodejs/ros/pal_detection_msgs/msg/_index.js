
"use strict";

let PersonDetection = require('./PersonDetection.js');
let LegDetections = require('./LegDetections.js');
let Detection2d = require('./Detection2d.js');
let FaceDetection = require('./FaceDetection.js');
let RecognizedObject = require('./RecognizedObject.js');
let FaceDetections = require('./FaceDetections.js');
let Detections2d = require('./Detections2d.js');
let RecognizedObjectArray = require('./RecognizedObjectArray.js');
let RotatedDetection2d = require('./RotatedDetection2d.js');
let RecognizedActions = require('./RecognizedActions.js');
let Gesture = require('./Gesture.js');
let TexturedObjectDetection = require('./TexturedObjectDetection.js');
let PersonDetections = require('./PersonDetections.js');
let WaveDetection = require('./WaveDetection.js');
let RecognizeObjectsGoal = require('./RecognizeObjectsGoal.js');
let RecognizeObjectsActionGoal = require('./RecognizeObjectsActionGoal.js');
let RecognizeObjectsFeedback = require('./RecognizeObjectsFeedback.js');
let RecognizeObjectsActionFeedback = require('./RecognizeObjectsActionFeedback.js');
let RecognizeObjectsAction = require('./RecognizeObjectsAction.js');
let RecognizeObjectsResult = require('./RecognizeObjectsResult.js');
let RecognizeObjectsActionResult = require('./RecognizeObjectsActionResult.js');

module.exports = {
  PersonDetection: PersonDetection,
  LegDetections: LegDetections,
  Detection2d: Detection2d,
  FaceDetection: FaceDetection,
  RecognizedObject: RecognizedObject,
  FaceDetections: FaceDetections,
  Detections2d: Detections2d,
  RecognizedObjectArray: RecognizedObjectArray,
  RotatedDetection2d: RotatedDetection2d,
  RecognizedActions: RecognizedActions,
  Gesture: Gesture,
  TexturedObjectDetection: TexturedObjectDetection,
  PersonDetections: PersonDetections,
  WaveDetection: WaveDetection,
  RecognizeObjectsGoal: RecognizeObjectsGoal,
  RecognizeObjectsActionGoal: RecognizeObjectsActionGoal,
  RecognizeObjectsFeedback: RecognizeObjectsFeedback,
  RecognizeObjectsActionFeedback: RecognizeObjectsActionFeedback,
  RecognizeObjectsAction: RecognizeObjectsAction,
  RecognizeObjectsResult: RecognizeObjectsResult,
  RecognizeObjectsActionResult: RecognizeObjectsActionResult,
};
