import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:mobile/attempt/attempts.tab.dart';
import 'package:mobile/users/users.tab.dart';

class MainScreen extends StatefulWidget {
  MainScreen({Key key, this.title}) : super(key: key);

  final String title;

  @override
  _MainScreenState createState() => _MainScreenState();
}

class _MainScreenState extends State<MainScreen> {
  int _selectedIndex = 0;

  static final List<Widget> _tabs = <Widget>[AttemptsTab(), UsersTab()];

  static final List<Widget> _tabTitle = <Widget>[
    Text('Attempts'),
    Text('Users')
  ];

  void _onChangeTab(int newIndex) {
    setState(() {
      this._selectedIndex = newIndex;
    });
  }

  @override
  Widget build(BuildContext context) => Scaffold(
        appBar: AppBar(
          title: _tabTitle.elementAt(_selectedIndex),
        ),
        bottomNavigationBar: BottomNavigationBar(
          items: const <BottomNavigationBarItem>[
            BottomNavigationBarItem(
                icon: Icon(Icons.sentiment_very_satisfied_rounded),
                label: "Attempts"),
            BottomNavigationBarItem(
                icon: Icon(Icons.account_box), label: "Users")
          ],
          currentIndex: _selectedIndex,
          onTap: _onChangeTab,
        ),
        body: Container(
          width: double.infinity,
          height: double.infinity,
          child: _tabs.elementAt(_selectedIndex),
        ),
      );
}
