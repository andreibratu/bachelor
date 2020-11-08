import 'dart:math';

import 'package:cross/redux/app.actions.dart';
import 'package:cross/redux/entry.entity.dart';
import 'package:cross/views/details.screen.dart';
import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_redux/flutter_redux.dart';
import 'package:intl/intl.dart';
import 'package:quartet/quartet.dart';
import 'package:redux/redux.dart';

class EntryCard extends StatelessWidget {
  final Entry entry;

  const EntryCard({Key key, this.entry}) : super(key: key);

  @override
  Widget build(BuildContext context) {
    var stringDate = DateFormat("dd MMM").format(entry.entryDate);
    var description =
        slice(entry.description, 0, min(30, entry.description.length));
    return StoreConnector(
        builder: (context, Store store) => GestureDetector(
            onTap: () {
              store.dispatch(
                  SetCurrentEntryAction(currEntry: Entry.copy(entry)));
              Navigator.push(context,
                  MaterialPageRoute(builder: (context) => DetailsScreen()));
            },
            child: Container(
                width: MediaQuery.of(context).size.width,
                height: 120,
                margin: EdgeInsets.all(2),
                child: Card(
                  color: entry.color,
                  child: Column(
                    children: [
                      Container(
                          padding: EdgeInsets.all(5),
                          child: Row(
                            children: [
                              Expanded(
                                  child: Text(
                                entry.title,
                                style: TextStyle(fontSize: 24),
                              )),
                              Text(stringDate)
                            ],
                          )),
                      Row(
                        children: [
                          Expanded(
                              child: Container(
                            padding: EdgeInsets.all(5),
                            child: Text(
                              description,
                              style: TextStyle(fontSize: 16),
                            ),
                          ))
                        ],
                      )
                    ],
                  ),
                ))),
        converter: (store) => store);
  }
}
