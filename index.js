require('bindings')('n2o')

module.exports = function () {
  console.log('-I ' + require('path').resolve(__dirname, 'n2o.gypi'));
}
