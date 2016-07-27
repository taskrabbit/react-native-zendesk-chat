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
	  this.state = { name: 'Anonymous', email: 'Anonymous', phone:'Anonymous'}
	  this._onPressButton = this._onPressButton.bind(this);
	}

	_onPressButton() {
		let { name, email, phone } = this.state
		ZendeskChat.startChat({
			name,
			email,
			phone,
		})
	}

	render() {
		return (
  <View style = {styles.container}>
    <TextInput style={styles.input} placeholder={'Name'}
      onChangeText={(name) => this.setState({name:name})}/>
    <TextInput style={styles.input} placeholder={'Email'}
      onChangeText={(email) => this.setState({email:email})}/>
    <TextInput style={styles.input} placeholder={'Phone'}
      onChangeText={(phone) => this.setState({phone:phone})}/>
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

