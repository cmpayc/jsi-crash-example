import { TurboModule, TurboModuleRegistry } from 'react-native';

export interface Spec extends TurboModule {
  readonly reverseString: (input: string, func: (res: string) => void) => string;
}

export default TurboModuleRegistry.getEnforcing<Spec>('NativeSampleModule');
