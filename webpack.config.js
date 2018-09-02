const path = require('path');
const outputDir = path.join(__dirname, "build/");

const isProd = process.env.NODE_ENV === 'production';
const ExtractTextPlugin = require("extract-text-webpack-plugin");
const HtmlWebpackPlugin = require("html-webpack-plugin");
const CleanWebpackPlugin = require("clean-webpack-plugin");


module.exports = {
  entry: './src/Index.bs.js',
  mode: isProd ? 'production' : 'development',
  output: {
    path: outputDir,
    // publicPath: outputDir,
    filename: '[name].[chunkhash].js',
  },
  module: {
    rules: 
    [
        { test: /\.scss$/,
        use: ExtractTextPlugin.extract({
          fallback: 'style-loader',
          use: [ 'css-loader', 'sass-loader' ]
          })
        }
    ]
  },
  plugins: [
    new ExtractTextPlugin('css/styles.css'),
    new HtmlWebpackPlugin({
      template: "./src/index.html"

    }),
    new CleanWebpackPlugin(["build"], {
      watch: false
    })
  ]
};
