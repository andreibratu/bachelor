import 'package:flutter/material.dart';
import 'package:flutter/widgets.dart';
import 'package:flutter_spinkit/flutter_spinkit.dart';

class LoadingScreen extends StatelessWidget {
  @override
  Widget build(BuildContext context) =>
      Scaffold(body: SpinKitHourGlass(color: Colors.blue));
}
