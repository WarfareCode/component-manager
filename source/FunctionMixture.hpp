#pragma once

#include <map>

#include <QtCore/QJsonArray>
#include <QtCore/QDebug>

#include "FunctionSignature.hpp"

namespace ComponentManager
{

/// Mixture adds a collection of functions to IComponentCreator.
class FunctionMixture
{

public:

  FunctionMixture(QJsonObject const &json)
  {
    QJsonValue jsonFunctions = json["functions"];

    if (jsonFunctions.isArray())
    {
      QJsonArray functionArray = jsonFunctions.toArray();

      for (int i = 0; i < functionArray.size(); ++i)
      {
        QJsonObject functionJson = functionArray[i].toObject();

        //---

        QString const name = functionJson["name"].toString();

        //---

        _functions[name] = Function::parseJsonArrayToFunctionSignatureTypes(functionJson,
                                                                            "signature");
      }
    }
  }

public:

  std::map<QString, Function::SignatureTypes> const &
  functions() const
  {
    return _functions;
  }

private:

  std::map<QString, Function::SignatureTypes> _functions;
};
}
