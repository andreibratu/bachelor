import 'package:cross/redux/app.actions.dart';
import 'package:cross/views/entry.card.dart';
import 'package:cross/views/form.screen.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:redux/redux.dart';

class MainScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return StoreConnector(
        builder: (context, Store store) => Scaffold(
            appBar: AppBar(title: Text("Mindful")),
            body: Container(
                height: double.infinity,
                width: double.infinity,
                child: Stack(
                  alignment: Alignment.bottomRight,
                  children: [
                    Container(
                      alignment: Alignment.center,
                      padding: EdgeInsets.only(top: 5),
                      child: store.state.entries.length != 0
                          ? ListView.builder(
                              itemCount: store.state.entries.length,
                              itemBuilder: (context, idx) =>
                                  EntryCard(entry: store.state.entries[idx]))
                          : Text(
                              "Why not add some entries?",
                              style: TextStyle(fontSize: 32),
                            ),
                    ),
                    Container(
                      width: 100,
                      height: 100,
                      padding: EdgeInsets.all(15),
                      child: FloatingActionButton(
                        backgroundColor: Colors.black,
                        onPressed: () {
                          store
                              .dispatch(SetCurrentEntryAction(currEntry: null));
                          Navigator.push(
                              context,
                              MaterialPageRoute(
                                  builder: (context) => FormScreen()));
                        },
                        child: Icon(
                          Icons.add,
                          color: Colors.white,
                        ),
                      ),
                    )
                  ],
                ))),
        converter: (store) => store);
  }
}
