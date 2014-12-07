if (process.env.__XCODE_BUILT_PRODUCTS_DIR_PATHS) {
  var path = require('path');
  require(path.join(process.env.__XCODE_BUILT_PRODUCTS_DIR_PATHS, 'n2o.node'));
} else {
  require('bindings')('n2o')
}

module.exports = function () {
  console.log('-I ' + require('path').resolve(__dirname, 'n2o.gypi'));
}
