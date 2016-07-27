import React, { Component } from 'react'
import {
  AppRegistry,
  StyleSheet,
  Text,
  TextInput,
  TouchableHighlight,
  View
} from 'react-native';
import ZendeskChat from '../node_modules/react-native-zendesk-chat'

export default class chatExample extends Component {
	constructor(props) {
	  super(props);
	  this.state = { name: 'test', email: 'test', phone:'test'}
	  this.onPressButton = this._onPressButton.bind(this);
	}

	_onPressButton() {
		// console.log(this.state.name)
		ZendeskChat.startChat({
			// name: this.state.name,
			// email: this.state.email,
			// phone: this.state.phone

			name: 'yy',
			email: 'yao4ever@hotmail.com',
			phone: '0172826880'
		})
	}

	render() {
		return (
  <View style = {styles.container}>
    <TextInput style={styles.input} placeholder={'Name'}
      onChangeText={(text) => this.setState({name:text})}/>
    <TextInput style={styles.input} placeholder={'Email'}
      onChangeText={(text) => this.setState({email:text})}/>
    <TextInput style={styles.input} placeholder={'Phone'}
      onChangeText={(text) => this.setState({phone:text})}/>
    <TouchableHighlight onPress={this._onPressButton}>
      <Text>Start Chatting</Text>
    </TouchableHighlight>
  </View>
  		);
	}
}

const styles = StyleSheet.create({
  container: {
    flex: 1,
    justifyContent: 'center',
    alignItems: 'center',
    backgroundColor: '#F5FCFF',
  },
  input: {
  	height: 40,
  	borderColor: 'gray',
  	borderWidth: 1,
  	marginLeft: 50,
  	marginRight: 50
  }
});

