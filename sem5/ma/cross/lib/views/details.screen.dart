import 'package:cross/redux/app.actions.dart';
import 'package:cross/views/form.screen.dart';
import 'package:cross/views/reusable/rounded.button.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:redux/redux.dart';

Color getTextColor(Color background) {
  return background.computeLuminance() > 0.5 ? Colors.black : Colors.white;
}

Color darken(Color c, [int percent = 10]) {
  assert(1 <= percent && percent <= 100);
  var f = 1 - percent / 100;
  return Color.fromARGB(c.alpha, (c.red * f).round(), (c.green * f).round(),
      (c.blue * f).round());
}

class DetailsScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) {
    return StoreConnector(
        builder: (context, Store store) => Scaffold(
                body: Container(
              padding: EdgeInsets.all(10),
              width: double.infinity,
              height: double.infinity,
              color: store.state.currEntry.color,
              child: Column(
                mainAxisSize: MainAxisSize.max,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  Container(
                    padding: EdgeInsets.only(top: 50),
                    child: Text(
                      store.state.currEntry.title,
                      style: TextStyle(
                          fontWeight: FontWeight.w800,
                          fontSize: 42,
                          color: getTextColor(store.state.currEntry.color)),
                    ),
                  ),
                  Container(
                    padding: EdgeInsets.only(top: 50),
                    child: Text(
                      store.state.currEntry.description,
                      style: TextStyle(
                          fontWeight: FontWeight.w600,
                          fontSize: 28,
                          color: getTextColor(store.state.currEntry.color)),
                    ),
                  ),
                  Spacer(flex: 4),
                  Container(
                    margin: EdgeInsets.only(bottom: 10),
                    child: Row(
                      mainAxisAlignment: MainAxisAlignment.spaceAround,
                      children: [
                        RoundedButton(
                            borderRadius: 15,
                            width: 100,
                            height: 50,
                            onPressed: () {
                              Navigator.pushReplacement(
                                  context,
                                  MaterialPageRoute(
                                      builder: (context) => FormScreen()));
                            },
                            child: Text("EDIT",
                                style: TextStyle(
                                    color: getTextColor(
                                        store.state.currEntry.color))),
                            color: darken(store.state.currEntry.color, 20),
                            disabledColor: Colors.blueGrey),
                        RoundedButton(
                          borderRadius: 15,
                          width: 100,
                          height: 50,
                          onPressed: () {
                            store.dispatch(DeleteEntryAction(
                                deleteId: store.state.currEntry.id));
                            store.dispatch(
                                SetCurrentEntryAction(currEntry: null));
                            Navigator.pop(context);
                          },
                          child: Text(
                            "DELETE",
                            style: TextStyle(
                                color:
                                    getTextColor(store.state.currEntry.color)),
                          ),
                          color: darken(store.state.currEntry.color, 20),
                          disabledColor: Colors.blueGrey,
                        )
                      ],
                    ),
                  )
                ],
              ),
            )),
        converter: (store) => store);
  }
}
