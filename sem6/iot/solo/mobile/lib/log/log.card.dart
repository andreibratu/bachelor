import 'dart:math';

import 'package:flutter/material.dart';
import 'package:intl/intl.dart';
import 'package:mobile/log/log.model.dart';

class LogCard extends StatelessWidget {
  final LogModel _log;
  static const TextStyle _BOLD = const TextStyle(fontWeight: FontWeight.bold);

  TextStyle _getBoldStyle(double? fontSize) =>
      (fontSize == null) ? _BOLD : _BOLD.copyWith(fontSize: fontSize);

  LogCard({Key? key, required LogModel log})
      : this._log = log,
        super(key: key);

  @override
  Widget build(BuildContext context) => Container(
      height: 300,
      width: double.infinity,
      child: Card(
        color: Colors.white70,
        shadowColor: Colors.blueGrey,
        child: Padding(
          padding: EdgeInsets.all(5),
          child: Row(children: [
            Expanded(
              flex: 4,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.spaceAround,
                crossAxisAlignment: CrossAxisAlignment.start,
                children: [
                  RichText(
                    text: TextSpan(
                      // Note: Styles for TextSpans must be explicitly defined.
                      // Child text spans will inherit styles from parent
                      style: Theme.of(context)
                          .textTheme
                          .bodyText1!
                          .copyWith(fontSize: 20),
                      children: <TextSpan>[
                        TextSpan(text: 'Phrase: ', style: _getBoldStyle(null)),
                        TextSpan(text: _log.getPhrasePretty()),
                      ],
                    ),
                  ),
                  RichText(
                    text: TextSpan(
                      // Note: Styles for TextSpans must be explicitly defined.
                      // Child text spans will inherit styles from parent
                      style: Theme.of(context).textTheme.bodyText1,
                      children: <TextSpan>[
                        TextSpan(
                            text: 'Keywords: ', style: _getBoldStyle(null)),
                        TextSpan(
                            text: _log.keywords.length != 0
                                ? _log.keywords.join(', ')
                                : 'Found none'),
                      ],
                    ),
                  ),
                ],
              ),
            ),
            Flexible(
              flex: 1,
              child: Column(
                mainAxisAlignment: MainAxisAlignment.center,
                crossAxisAlignment: CrossAxisAlignment.center,
                children: [
                  Text(
                    DateFormat('HH').format(_log.logDate).toUpperCase(),
                    style: _getBoldStyle(30),
                  ),
                  Text(
                    DateFormat('MM').format(_log.logDate).toString(),
                    style: _getBoldStyle(30),
                  ),
                  Text(DateFormat('d MMMM').format(_log.logDate).toUpperCase()),
                  Text(_log.logDate.year.toString())
                ],
              ),
            )
          ]),
        ),
      ));
}
