import 'package:cross/redux/app.actions.dart';
import 'package:cross/redux/entry.entity.dart';
import 'package:cross/views/reusable/rounded.button.dart';
import 'package:cross/views/reusable/unfocus.scaffold.dart';
import 'package:flutter/cupertino.dart';
import 'package:flutter/material.dart';
import 'package:flutter_colorpicker/flutter_colorpicker.dart';
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

class FormScreen extends StatefulWidget {
  @override
  State<StatefulWidget> createState() => _FormScreenState();
}

class _FormScreenState extends State<FormScreen> {
  final entryTitleController = TextEditingController();
  final entryTextController = TextEditingController();
  Color currentColor = Colors.white;

  @override
  void initState() {
    super.initState();
  }

  void dispose() {
    [entryTitleController, entryTextController]
        .forEach((TextEditingController element) => element.dispose());
    super.dispose();
  }

  @override
  Widget build(BuildContext context) {
    return StoreConnector(
        onInit: (store) {
          var currEntry = store.state.currEntry;
          if (currEntry != null) {
            entryTitleController.text = currEntry.title;
            entryTextController.text = currEntry.description;
            currentColor = currEntry.color;
          }
        },
        builder: (context, Store store) => UnfocusScaffold(
                body: Container(
              color: currentColor,
              width: double.infinity,
              height: double.infinity,
              padding: EdgeInsets.all(20),
              child: Column(
                children: [
                  Container(
                      padding: EdgeInsets.only(top: 30),
                      alignment: Alignment.centerLeft,
                      child: Text(
                        store.state.currEntry == null
                            ? "Create entry"
                            : "Edit entry",
                        style: TextStyle(
                          fontSize: 32,
                          fontWeight: FontWeight.w800,
                          color: getTextColor(currentColor),
                        ),
                        textAlign: TextAlign.left,
                      )),
                  // Enter entry title input
                  Container(
                    width: double.infinity,
                    padding: EdgeInsets.only(top: 30),
                    child: TextField(
                      style: TextStyle(
                          color: getTextColor(currentColor), fontSize: 36),
                      controller: entryTitleController,
                      keyboardType: TextInputType.emailAddress,
                      decoration: InputDecoration(hintText: "Entry title"),
                    ),
                  ),
                  // Enter entry text textarea
                  Container(
                    width: double.infinity,
                    padding: EdgeInsets.only(top: 20),
                    child: TextField(
                      style: TextStyle(
                          color: getTextColor(currentColor), fontSize: 20),
                      maxLines: 15,
                      controller: entryTextController,
                      decoration:
                          InputDecoration(hintText: "Entry description"),
                    ),
                  ),
                  Spacer(flex: 4),
                  Container(
                    alignment: Alignment.center,
                    width: double.infinity,
                    child: RoundedButton(
                      borderRadius: 15,
                      width: 500,
                      height: 60,
                      color: darken(currentColor, 20),
                      child: Text(
                        "PICK COLOR",
                        style: TextStyle(
                            color: getTextColor(darken(currentColor, 20))),
                      ),
                      disabledColor: null,
                      onPressed: () {
                        showDialog(
                          context: context,
                          child: AlertDialog(
                            title: const Text('Pick a color!'),
                            content: SingleChildScrollView(
                              child: ColorPicker(
                                pickerColor: currentColor,
                                onColorChanged: (Color newColor) =>
                                    setState(() => currentColor = newColor),
                                showLabel: true,
                                pickerAreaHeightPercent: 0.8,
                              ),
                            ),
                            actions: <Widget>[
                              FlatButton(
                                child: const Text('Got it'),
                                onPressed: () {
                                  Navigator.of(context).pop();
                                },
                              ),
                            ],
                          ),
                        );
                      },
                    ),
                  ),
                  // Submit button
                  Spacer(flex: 1),
                  Container(
                    alignment: Alignment.center,
                    width: double.infinity,
                    child: RoundedButton(
                        borderRadius: 15,
                        width: 500,
                        height: 60,
                        onPressed: () {
                          var isAdd = store.state.currEntry == null;
                          if (isAdd) {
                            store.dispatch(AddEntryAction(
                                newEntry: Entry(
                                    color: currentColor,
                                    description: entryTextController.text,
                                    title: entryTitleController.text)));
                          } else {
                            var editEntry = Entry.copy(store.state.currEntry);
                            editEntry.color = currentColor;
                            editEntry.title = entryTitleController.text;
                            editEntry.description = entryTextController.text;
                            store.dispatch(
                                EditEntryAction(editedEntry: editEntry));
                          }
                          Navigator.pop(context);
                        },
                        child: Text(
                            store.state.currEntry == null ? "ADD" : "EDIT",
                            style: TextStyle(
                                color:
                                    getTextColor(getTextColor(currentColor)))),
                        color: getTextColor(currentColor),
                        disabledColor: Colors.blueGrey),
                  )
                ],
              ),
            )),
        converter: (store) => store);
  }
}
