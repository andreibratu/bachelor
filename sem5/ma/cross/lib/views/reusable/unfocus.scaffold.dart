import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';

/*
A wrapper around scaffold that allows user to
unfocus keyboard when clicking on the background.
*/
class UnfocusScaffold extends StatelessWidget {
  final Widget body;

  UnfocusScaffold({@required this.body});

  @override
  Widget build(BuildContext context) {
    return GestureDetector(
        onTap: () {
          FocusScope.of(context).requestFocus(new FocusNode());
        },
        child: Scaffold(body: body));
  }
}
