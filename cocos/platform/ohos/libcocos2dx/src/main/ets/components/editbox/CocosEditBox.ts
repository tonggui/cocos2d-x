import hilog from '@ohos.hilog';

export class TextInputInfo {
    public index: number = 0;

    public x: number = 0;
    public y: number = 0;

    public w: number = 0;
    public h: number = 0;

    public paddingW: number = 0;
    public paddingH: number = 0;

    public fontSize: number = 0;
    public fontColor: FontColor = new FontColor(0, 0, 0, 0);
    public fontPath: string = '';

    public placeholderFontSize: number = 0;
    public placeholderFontColor: FontColor = new FontColor(0, 0, 0, 0);
    public placeHolder: string = '';
    public placeHolderFontPath: string = '';

    public maxLength = 0;

    public inputMode = InputType.Normal;

    public visibility = Visibility.Hidden;

    public text: string = '';
}

class FontColor {
    public r: number = 0;
    public g: number = 0;
    public b: number = 0;
    public a: number = 0;

    constructor(r: number, g: number, b: number, a: number) {
        this.r = r;
        this.g = g;
        this.b = b;
        this.a = a;
    }
}

export default class CocosEditBox {
    private static index = 0;

    private static parentPort;

    static init(parentPort) {
        CocosEditBox.parentPort = parentPort;
    }

    static postCreateCocosEditBox(index: number, x: number, y: number, w: number, h: number) {
        //hilog.info(0x0000, 'myTestTag', 'create textinput post');
        //CocosEditBox.parentPort.postMessage({ 'function': 'createCocosEditBox', 'index': index, 'x': x, 'y': y, 'w': w, 'h': h });
    }

    static postSetEditBoxViewRect(x: number, y: number, w: number, h: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxViewRect', 'x': x, 'y': y, 'w': w, 'h': h });
    }

    static postSetEditBoxVisable(x: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxVisable', 'x': x});
    }

    static postSetCurrentIndex(index: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setCurrentIndex', 'index': index });
    }

    static postSetCurrentText(text: string) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setCurrentText', 'text': text });
    }

    static postSetEditBoxPadding(paddingW: number, paddingH: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxPadding', 'paddingW': paddingW, 'paddingH': paddingH });
    }

    static postSetEditBoxFontSize(size: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxFontSize', 'size': size });
    }

    static postSetEditBoxFontColor(r: number, g: number, b: number, a: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxFontColor', 'r': r, 'g': g, 'b': b, 'a': a });
    }

    static postSetEditBoxPlaceHolderFontColor(r: number, g: number, b: number, a: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxPlaceHolderFontColor', 'r': r, 'g': g, 'b': b, 'a': a });
    }

    static postSetEditBoxPlaceHolderFontSize(size: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxPlaceHolderFontSize', 'size': size });
    }

    static postSetEditBoxPlaceHolder(text: string) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxPlaceHolder', 'text': text });
    }

    static postSetEditBoxMaxLength(maxLength: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxMaxLength', 'maxLength': maxLength });
    }

    static postSetNativeInputMode(inputMode: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setNativeInputMode', 'inputMode': inputMode });
    }

    static postSetNativeInputFlag(inputFlag: number) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setNativeInputFlag', 'inputFlag': inputFlag });
    }

    static postSetEditBoxFontPath(fontPath: string) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxFontPath', 'fontPath': fontPath });
    }

    static postSetEditBoxPlaceHolderFontPath(fontPath: string) {
        CocosEditBox.parentPort.postMessage({ 'function': 'setEditBoxPlaceHolderFontPath', 'fontPath': fontPath });
    }

    static createCocosEditBox(index: number, x: number, y: number, w: number, h: number) {
        //hilog.info(0x0000, 'myTestTag', 'create textinput js');
        //globalThis.textInputArray.push(new TextInputInfo(index, x, y, w, h));
        //hilog.info(0x0000, 'myTestTag', 'create textinput js finish');
    }

    static setEditBoxViewRect(x: number, y: number, w: number, h: number) {
        globalThis.textInputInfo.x = x;
        globalThis.textInputInfo.y = y;
        globalThis.textInputInfo.w = w;
        globalThis.textInputInfo.h = h;
    }

    static setEditBoxVisable(x: number) {
        if (x > 0) {
            globalThis.textInputInfo.visibility = Visibility.Visible;
        } else {
            globalThis.textInputInfo.visibility = Visibility.Hidden;
        }
    }

    static setCurrentIndex(index: number) {
        globalThis.textInputInfo.index = index;
    }

    static setCurrentText(text: string) {
        globalThis.textInputInfo.text = text;
    }

    static setEditBoxPadding(paddingW: number, paddingH: number) {
        globalThis.textInputInfo.paddingW = paddingW;
        globalThis.textInputInfo.paddingH = paddingH;
    }

    static setEditBoxFontSize(size: number) {
        globalThis.textInputInfo.fontSize = size;
    }

    static setEditBoxFontColor(r: number, g: number, b: number, a: number) {
        globalThis.textInputInfo.fontColor = new FontColor(r, g, b, a/255);
    }

    static setEditBoxPlaceHolderFontColor(r: number, g: number, b: number, a: number) {
        globalThis.textInputInfo.placeholderFontColor = new FontColor(r, g, b, a/255);
    }

    static setEditBoxPlaceHolderFontSize(size: number) {
        globalThis.textInputInfo.placeholderFontSize = size;
    }

    static setEditBoxPlaceHolder(text: string) {
        globalThis.textInputInfo.placeHolder = text;
    }

    static setEditBoxMaxLength(maxLength: number) {
        globalThis.textInputInfo.maxLength = maxLength;
    }

    static setNativeInputMode(inputMode: number) {
        switch (inputMode) {
            case 0:
            case 4:
            case 6:
                globalThis.textInputInfo.inputMode = InputType.Normal;
                break;
            case 2:
            case 5:
                globalThis.textInputInfo.inputMode = InputType.Number;
                break;
            case 3:
                globalThis.textInputInfo.inputMode = InputType.PhoneNumber;
                break;
            case 1:
                globalThis.textInputInfo.inputMode = InputType.Email;
                break;
            default:
                break;
        }
    }

    static setNativeInputFlag(inputFlag: number) {
        if (inputFlag > 0) {
            globalThis.textInputInfo.inputMode = InputType.Password;
        }
    }

    static setEditBoxFontPath(fontPath: string) {
        globalThis.textInputInfo.fontPath = fontPath;
    }

    static setEditBoxPlaceHolderFontPath(fontPath: string) {
        globalThis.textInputInfo.placeHolderFontPath = fontPath;
    }

    static getNativeText(): string {
        let tempText = globalThis.textInputInfo.text;
        globalThis.textInputInfo.text = '';
        return tempText;
    }
}

globalThis.CocosEditBox = {}
globalThis.CocosEditBox.createCocosEditBox = CocosEditBox.postCreateCocosEditBox;
globalThis.CocosEditBox.setEditBoxViewRect = CocosEditBox.postSetEditBoxViewRect;
globalThis.CocosEditBox.setEditBoxVisable = CocosEditBox.postSetEditBoxVisable;
globalThis.CocosEditBox.setCurrentIndex = CocosEditBox.postSetCurrentIndex;
globalThis.CocosEditBox.setCurrentText = CocosEditBox.postSetCurrentText;
globalThis.CocosEditBox.setEditBoxPadding = CocosEditBox.postSetEditBoxPadding;
globalThis.CocosEditBox.setEditBoxPlaceHolder = CocosEditBox.postSetEditBoxPlaceHolder;
globalThis.CocosEditBox.setEditBoxFontSize = CocosEditBox.postSetEditBoxFontSize;
globalThis.CocosEditBox.setEditBoxFontColor = CocosEditBox.postSetEditBoxFontColor;
globalThis.CocosEditBox.setEditBoxFontPath = CocosEditBox.postSetEditBoxFontPath;
globalThis.CocosEditBox.setEditBoxPlaceHolderFontSize = CocosEditBox.postSetEditBoxPlaceHolderFontSize;
globalThis.CocosEditBox.setEditBoxPlaceHolderFontColor = CocosEditBox.postSetEditBoxPlaceHolderFontColor;
globalThis.CocosEditBox.setEditBoxPlaceHolderFontPath = CocosEditBox.postSetEditBoxPlaceHolderFontPath;
globalThis.CocosEditBox.setEditBoxMaxLength = CocosEditBox.postSetEditBoxMaxLength;
globalThis.CocosEditBox.setNativeInputMode = CocosEditBox.postSetNativeInputMode;
globalThis.CocosEditBox.setNativeInputFlag = CocosEditBox.postSetNativeInputFlag;
globalThis.CocosEditBox.getNativeText = CocosEditBox.getNativeText;