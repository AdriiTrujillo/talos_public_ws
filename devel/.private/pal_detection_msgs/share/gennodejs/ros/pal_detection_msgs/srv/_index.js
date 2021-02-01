
"use strict";

let SelectTexturedObject = require('./SelectTexturedObject.js')
let Recognizer = require('./Recognizer.js')
let SetDatabase = require('./SetDatabase.js')
let AddTexturedObject = require('./AddTexturedObject.js')
let StopEnrollment = require('./StopEnrollment.js')
let ChangeObjectRecognizerModel = require('./ChangeObjectRecognizerModel.js')
let StartEnrollment = require('./StartEnrollment.js')

module.exports = {
  SelectTexturedObject: SelectTexturedObject,
  Recognizer: Recognizer,
  SetDatabase: SetDatabase,
  AddTexturedObject: AddTexturedObject,
  StopEnrollment: StopEnrollment,
  ChangeObjectRecognizerModel: ChangeObjectRecognizerModel,
  StartEnrollment: StartEnrollment,
};
