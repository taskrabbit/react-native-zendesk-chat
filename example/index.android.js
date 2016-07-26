import React, { Component } from 'react';
import {
  AppRegistry,
} from 'react-native';
import App from './src/chat';

const app = new App();

AppRegistry.registerComponent('example', () => app);
