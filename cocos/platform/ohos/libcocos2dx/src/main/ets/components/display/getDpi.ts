import display from '@ohos.display';

export default class CCDisplayUtils {
    static displayClass;

    static init() {
        try {
            CCDisplayUtils.displayClass = display.getDefaultDisplaySync();
        } catch (exception) {
            console.error('Failed to obtain the default display object. Code: ' + JSON.stringify(exception));
        }
    }

    static getDpi() : number {
        return CCDisplayUtils.displayClass.densityDPI;
    }
}

CCDisplayUtils.init();
globalThis.CCDisplayUtils = {};
globalThis.CCDisplayUtils.getDpi=CCDisplayUtils.getDpi;